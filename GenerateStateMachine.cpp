#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;


class Transition
{
public:
    Transition(string _s1, string _s2, string _e) :
        m_state1(_s1),
        m_state2(_s2),
        m_event(_e)
    {}

    string m_state1;
    string m_state2;
    string m_event;
};

template <class CONTAINER, class ITEM>
void add_once(CONTAINER& container, ITEM item)
{
    if (find(container.begin(), container.end(), item) == container.end())
    {
        container.push_back(item);
    }
}

class Transitions
{
public:

    bool Add(Transition _t)
    {
        add_once(m_states, _t.m_state1);
        add_once(m_states, _t.m_state2);
        add_once(m_events, _t.m_event);

        if (m_transitions[_t.m_state1].find(_t.m_event) != m_transitions[_t.m_state1].end())
        {
            cout << "error - this transition already exists: " << _t.m_state1 << " " << _t.m_event << " " << _t.m_state2 << endl;
            cout << m_transitions[_t.m_state1][_t.m_event] << endl;
            return false;
        }
        
        m_transitions[_t.m_state1][_t.m_event] = _t.m_state2;
        cout << "m_transitions[" << _t.m_state1 << "][" << _t.m_event << "] == " << m_transitions[_t.m_state1][_t.m_event] << endl;

        return true;
    }

    void CreateHeaderFile(string& headerfilename, string& sourcefilename, string& classname)
    {
        ofstream myfile;
        myfile.open(headerfilename);
        myfile << "#pragma once" << endl;
        myfile << "#include <cassert>" << endl;
        myfile << "#include <iostream>" << endl;
        myfile << "#define COUT std::cout << __PRETTY_FUNCTION__ << \": \" " << endl;
        myfile << endl;
        myfile << "class " << classname << "{" << endl;
        myfile << "public:"<< endl;

        myfile << "    enum State" << "{" << endl;
        for (auto it = m_states.begin(); it != m_states.end(); ++it)
        
{
            myfile << "        " << *it;
            if((it + 1) != m_states.end())
            {
                myfile << ",";
            }
            myfile << endl;
        }
        myfile << "    };"<< endl;
        myfile << endl;

        myfile << "State m_state;" << endl;


        for (auto it = m_states.begin(); it != m_states.end(); ++it)
        {
            myfile << "    void Enter_" << *it << "();" << endl;
        }
        myfile << endl;



        myfile << "    const char* ToString(const State _state)" << endl;
        myfile << "    {" << endl;
        myfile << "        const char* retval;" << endl;
        myfile << "        switch (_state)" << endl;
        myfile << "        {" << endl;
        for (auto it = m_states.begin(); it != m_states.end(); ++it)
        {
            myfile << "        case " << *it << ":" << endl;
            myfile << "            retval = \"" << *it << "\";" << endl;
            myfile << "            break;" << endl;
        }

        myfile << "        default: assert(0); break;" << endl;
        myfile << "        }" << endl;
        myfile << "        return retval;" << endl;
        myfile << "    }" << endl;
        myfile << endl;

        myfile << "    enum Event" << "{" << endl;
        myfile << "        event_null," << endl;
        for (auto it = m_events.begin(); it != m_events.end(); ++it)
        {
            myfile << "        " << *it;
            if((it + 1) != m_events.end())
            {
                myfile << ",";
            }
            myfile << endl;
        }
        myfile << "    };"<< endl;
        myfile << endl;



        myfile << "    const char* ToString(const Event _event)" << endl;
        myfile << "    {" << endl;
        myfile << "        const char* retval;" << endl;
        myfile << "        switch (_event)" << endl;
        myfile << "        {" << endl;
        for (auto it = m_events.begin(); it != m_events.end(); ++it)
        {
            myfile << "        case " << *it << ":" << endl;
            myfile << "            retval = \"" << *it << "\";" << endl;
            myfile << "            break;" << endl;
        }

        myfile << "        default: assert(0); break;" << endl;
        myfile << "        }" << endl;
        myfile << "        return retval;" << endl;
        myfile << "    }" << endl;
        myfile << endl;



        myfile << "    void SetState(State _state)" << endl;
        myfile << "    {" << endl;
        myfile << "        m_state = _state;" << endl;
        myfile << "        std::cout <<  \"state: \" << ToString(m_state) << std::endl;" << endl;
        myfile << "    }" << endl;

        

        for (auto it = m_transitions.begin(); it != m_transitions.end(); ++it)
        {
            myfile << "    Event " << it->first << "_handle_event(Event _event)" << endl;
            myfile << "    {" << endl;
            myfile << "        switch (_event)" << endl;
            myfile << "        {" << endl;

            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                myfile << "        case " << it2->first << ":" << endl;
                myfile << "            SetState(" << it2->second <<");" << endl;
                myfile << "            Enter_" << it2->second << "();" << endl;
                myfile << "            break;" << endl;
            }

            myfile << "            default: _event = event_null; break;" << endl;
            myfile << "        }" << endl;
            myfile << "    }" << endl;

        }
        myfile << endl;



        myfile << "    State HandleEvent(Event _event)" << endl;
        myfile << "    {" << endl;
        myfile << "        while (_event != event_null)" << endl;
        myfile << "        {" << endl;
        myfile << "            switch(m_state)" << endl;
        myfile << "            {" << endl;

        for (auto it = m_states.begin(); it != m_states.end(); ++it)
        {
            myfile << "            case " << *it << ":" << endl;
            myfile << "                _event = " << *it << "_handle_event(_event);" << endl;
            myfile << "                break;" << endl;
        }





        myfile << "            }" << endl;



        myfile << "        }" << endl;
        myfile << "    }" << endl;
        myfile << "};"<< endl;

        myfile.close();

        myfile.open(sourcefilename);

        myfile << "#include \"" << headerfilename << "\"" << endl;
        for (auto it = m_states.begin(); it != m_states.end(); ++it)
        {
            myfile << "void " << classname << "::" << "Enter_" << *it << "()" << endl;
            myfile << "{" << endl;
            myfile << "}" << endl;
        }

        myfile.close();
        
    }

private:
    map<string, map<string, string> > m_transitions; // state1[event] = state2
    vector<string> m_states;
    vector<string> m_events;

};

int main(int argc, char* argv[])
{
    if (argc < 5) 
    {
        cout << "ERROR!" << endl;
        exit(-1);
    }
    string flag1(argv[1]);
    string infile(argv[2]);
    string flag2(argv[3]);
    string classname(argv[4]);
    string outheaderfile(classname);
    outheaderfile += ".h";
    string outsourcefile(classname);
    outsourcefile += ".cpp";

    Transitions transitions;

    cout << "argc: " << argc << infile << endl;

    ifstream dotfile(infile);
    string content;

    bool inside_digraph = false;
    int first_space, arrow, second_space, open_bracket, close_bracket, label;

    while (getline(dotfile, content))
    {
        string state1, state2, event;

        if ((inside_digraph) && (content.find_first_of("label=") != string::npos))
        {
            first_space = content.find_first_of(" ");

            if(first_space != string::npos)
            {
                state1 = string(content, 0, first_space);
                content.erase(0, first_space);
            
                //cout << "state1: " << state1 << ". " ;
            }

            content.erase(0, 4);

            if ((open_bracket = content.find_first_of("[")) != string::npos)
            {
                state2 = string(content, 0, open_bracket);
                //cout << "state2: " << state2 << ". ";
            }

            if ((label = content.find_first_of("label=\"") != string::npos))
            {
                content.erase(0, open_bracket + 8);
                if ((string::npos != (close_bracket = content.find_first_of("\""))))
                {
                    event = string(content, 0, close_bracket);
                    //cout << "event: " << event << endl;
                }
            }
        }

        if ((state1.length() > 0) &&
            (state2.length() > 0) &&
            (event.length() > 0))
        {
            if (! transitions.Add(Transition(state1, state2, event)))
                exit(-1);
        }

        if (content == "digraph{" ) inside_digraph = true;
        if (content == "}" ) inside_digraph = false;

    }

    size_t end = infile.find_first_of(".dot");
    
    transitions.CreateHeaderFile(outheaderfile, outsourcefile, classname);

    return 0;
}
