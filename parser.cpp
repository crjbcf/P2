//
// Created by chris on 4/1/2023.
//

#include "parser.h"

//set global token
static Token tk;
fstream file;

int lineNum = 1;


node_t* getNode(string label)
{
    node_t* node = new node_t;
    node->label = label;

    return node;
}

void error() {
    cout << "There was an error.";
    cout << "\ntoken: " << tk.tokenInstance << " line number: " << lineNum;
    exit(0); //terminate program
}

//<K> -> t1 || t3
node_t* K()
{
    node_t* p = getNode("K");

    if (tk.tokenID == T1_tk)
    {
        p->tokens.push_back(tk);
        tk = scanner(file, lineNum);
        return p;
    }
    else if (tk.tokenID == T3_token)
    {
        p->tokens.push_back(tk);
        tk = scanner(file, lineNum);
        return p;
    }
    else
    {
        error(); // expected T1 or T3
    }

    return nullptr;
}




//<H> -> { || }
node_t* H()
{
    node_t* p = getNode("H");
    if (tk.tokenID == T2_token)
    {
        if (tk.tokenInstance == "{") //predict {
        {
            p->tokens.push_back(tk);
            tk = scanner(file, lineNum);

            return p; //end of rule

        }
        else if (tk.tokenInstance == "}")
        {
            p->tokens.push_back(tk);
            tk = scanner(file, lineNum);

            return p; //end of rule
        }
        else
        {
            error(); //{ or } expected
        }
    }
    else
    {
        error(); //T2 expected
    }

    return nullptr;
}



//<M> -> <K><H> || empty
node_t* M()
{
    //kinda unsure what to do here....
    //gonna go based of current token
    node_t* p = getNode("M");
    if (tk.tokenID == T1_tk || tk.tokenID == T3_token) //since Ks first set is t1 or t3
    {
        p->child1 = K(); // predict K

        p->child2 = H(); //predict H

        return p; //end of production
    }
    else
        return nullptr; //empty?

}

//<G> -> <K><M>
node_t* G()
{
    node_t* p = getNode("G");

    p->child1 = K(); // predict K

    p->child2 = M(); // predict M

    return p; //end of production rule
}


//<F> -> |<G>~
node_t* F()
{
    node_t* p = getNode("F");

    if (tk.tokenID == T2_token)
    {
        if (tk.tokenInstance == "|")
        {
            p->tokens.push_back(tk);
            tk = scanner(file, lineNum);

            p->child1 = G(); //predict G

            if (tk.tokenID == T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    p->tokens.push_back(tk);
                    tk = scanner(file, lineNum);

                    return p; // end of production rule
                }
                else
                {
                    error(); //expected ~
                }
            }
            else
            {
                error(); //expected T2
            }
        }
        else
        {
            error(); // expected |
        }
    }
    else
    {
        error(); //expected T2
    }

    return nullptr;
}

//<E> -> ]<K>~
node_t* E()
{
    node_t* p = getNode("E");

    if (tk.tokenID == T2_token)
    {
        if (tk.tokenInstance == "]")
        {
            p->tokens.push_back(tk);
            tk = scanner(file, lineNum);

            p->child1 = K(); //predict K

            if (tk.tokenID == T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    p->tokens.push_back(tk);
                    tk = scanner(file, lineNum);

                    return p; // end of production rule
                }
                else
                {
                    error(); //expected ~
                }
            }
            else
            {
                error(); //expected T2
            }
        }
        else
        {
            error(); // expected ]
        }
    }
    else
    {
        error(); //expected T2
    }

    return nullptr;
}

//<D> -> [t1
node_t* D()
{
    node_t* p = getNode("D");

    if (tk.tokenID == T2_token) //predict T2
    {
        if (tk.tokenInstance == "[") //predict [
        {
            p->tokens.push_back(tk);

            tk = scanner(file, lineNum);

            if (tk.tokenID == T1_tk) //predict T1
            {
                p->tokens.push_back(tk);
                tk = scanner(file, lineNum);

                return p;
            }
            else
            {
                error();
            }
        }
        else
        {
            error(); // expected "["
        }
    }
    else
    {
        error();//expected T2
    }

    return nullptr;
}

//<C> -> *<K>
node_t* C()
{
    node_t* p = getNode("C");

    if (tk.tokenID == T2_token)//* is a T2 token
    {
        if (tk.tokenInstance == "*")
        {
            p->tokens.push_back(tk);
            tk = scanner(file, lineNum);

            p->child1 = K(); //predicting K

            return p; // end of production rule
        }
        else
        {
            error(); //* expected
        }
    }
    else
    {
        error(); //tk2 expected
    }

    return nullptr;
}

//<L> -> <D>~ || <E>~ || <F>~ || empty
node_t* L()
{
    node_t* p = getNode("L");
    //first check for T2 token (first sets for non terms are all t2 tokens
    if (tk.tokenID == T2_token)
    {
        //check which instance it is which will decide which rule to follow
        if (tk.tokenInstance == "[") // choose D path
        {
           p->child1 = D(); // predict D

            if (tk.tokenID = T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    p->tokens.push_back(tk);
                    tk = scanner(file, lineNum);

                    return p; //end of rule
                }
                else
                {
                    error(); //expected ~
                }
            }
            else
            {
                error(); //expected T2
            }
        }
        else if (tk.tokenInstance == "]") //E path
        {
             p->child1 = E(); //predict E

            if (tk.tokenID = T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    p->tokens.push_back(tk);
                    tk = scanner(file, lineNum);

                    return p; //end of rule
                }
                else
                {
                    error(); //expected ~
                }
            }
            else
            {
                error(); //expected T2
            }
        }
        else if (tk.tokenInstance == "|") //F path
        {
            p->child1 = F(); //predict f

            if (tk.tokenID = T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    p->tokens.push_back(tk);
                    tk = scanner(file, lineNum);

                    return p; //end of rule
                }
                else
                {
                    error(); //expected ~
                }
            }
            else
            {
                error(); //expected T2
            }
        }
    }
    else
    {
        return nullptr; //empty?
    }
    return nullptr;
}


node_t* J()
{
    node_t* p = getNode("J");
    //first check for t1 or t2 in current token if not one of these we are in empty case
    if (tk.tokenID == T2_token) //its one of the first few rules
    {
        if (tk.tokenInstance == "*") //process C rule
        {
            p->child1 = C(); //predict C

            if (tk.tokenID == T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    p->tokens.push_back(tk);
                    tk = scanner(file, lineNum);

                    p->child2 = J(); //predict J

                    if (tk.tokenID == T2_token)
                    {
                        if (tk.tokenInstance == "~")
                        {
                            p->tokens.push_back(tk);
                            tk = scanner(file, lineNum);

                            p->child3 = L(); //predict L

                            return p; //end of production rule 1
                        }
                        else
                        {
                            error(); //predicted ~
                        }
                    }
                    else
                    {
                        error(); //predicted T2
                    }
                }
                else
                {
                    error(); //expected ~
                }
            }
            else
            {
                error(); //expected T2
            }


        }
        else if (tk.tokenInstance == "[") //process <D> rule
        {
            p->child1 = D(); //predict D

            if (tk.tokenID == T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    p->tokens.push_back(tk);
                    tk = scanner(file, lineNum);

                    p->child2 = J(); //predict J

                    return p ; //end of production 2
                }
                else
                {
                    error(); //predict ~
                }
            }
            else
            {
                error();//predicted T2

            }
        }
        else if (tk.tokenInstance == "]") //process <E> rule
        {
            p->child1 = E(); //predict E

            if (tk.tokenID == T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    p->tokens.push_back(tk);
                    tk = scanner(file, lineNum);

                    p->child2 = J(); //predict J

                    return p; //end of rule 3
                }
                else
                {
                    error(); //predicted ~
                }
            }
            else
            {
                error(); //predicted T2
            }
        }
        else
        {
            error(); //expected * or [ or ]
        }
    }
    else if (tk.tokenID == T1_tk) //its the 4th rule
    {
        p->child1 = F(); //predict F

        if (tk.tokenID == T2_token)
        {
            if (tk.tokenInstance == "~")
            {
                p->tokens.push_back(tk);
                tk = scanner(file, lineNum); //consume

                p->child2 = J(); //predict J

                return p; //end of rule 4
            }
            else
            {
                error(); //expected ~
            }
        }
        else
        {
            error(); //expected T2
        }

    }
    else
    {
        return nullptr; //empty?
    }

    return nullptr;
}

//A -> ^t1<A> || empty
node_t* A()
{
    if (tk.tokenID == T2_token) //^ is a t2 token
    {
        if (tk.tokenInstance == "^") //make sure it is the expected ^
        {
            node_t* p = getNode("A");

            p->tokens.push_back(tk);

            tk = scanner(file, lineNum);

            if (tk.tokenID == T1_tk)
            {
                p->tokens.push_back(tk);
                tk = scanner(file, lineNum);

                p->child1 = A(); //predicting A

                return p;
            }
        }
        else
        {
            error();// ^ was the expected terminal so output error.
        }
    }
    else
    {

        return nullptr; //empty
    }

    return nullptr;

}


// <S> -> <S> -> <A><J>
node_t* S()
{
    node_t* p = getNode("S");

    p->child1 = A(); //predicting A

    p->child2 = J(); //predicting J

    return p; //end of production
}


node_t* parser(fstream &file)
{
    node_t* root;
    tk = scanner(file, lineNum);

    root = S(); //start with starting nonTerm S

    if (tk.tokenID == EOF_token)
        cout << "Parse Success";
    else
        error();

    return root;
}
