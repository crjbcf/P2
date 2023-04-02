//
// Created by chris on 4/1/2023.
//

#include "parser.h"

//set global token
static Token tk;
fstream file;

int lineNum = 1;

void error() {
    cout << "There was an error.";
    cout << "\ntoken: " << tk.tokenInstance << " line number: " << lineNum;
    exit(0); //terminate program
}

//<K> -> t1 || t3
void K()
{
    if (tk.tokenID == T1_tk)
    {
        tk = scanner(file, lineNum);
    }
    else if (tk.tokenID == T3_token)
    {
        tk = scanner(file, lineNum);
    }
    else
    {
        error(); // expected T1 or T3
    }
}




//<H> -> { || }
void H()
{
    if (tk.tokenID == T2_token)
    {
        if (tk.tokenInstance == "{") //predict {
        {
            tk = scanner(file, lineNum);

            return; //end of rule

        }
        else if (tk.tokenInstance == "}")
        {
            tk = scanner(file, lineNum);

            return; //end of rule
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
}



//<M> -> <K><H> || empty
void M()
{
    //kinda unsure what to do here....
    //gonna go based of current token
    if (tk.tokenID == T1_tk || tk.tokenID == T3_token) //since Ks first set is t1 or t3
    {
        K(); // predict K

        H(); //predict H

        return; //end of production
    }
    else
        return; //empty?

}

//<G> -> <K><M>
void G()
{

    K(); // predict K

    M(); // predict M

    return; //end of production rule
}


//<F> -> |<G>~
void F()
{
    if (tk.tokenID == T2_token)
    {
        if (tk.tokenInstance == "|")
        {
            tk = scanner(file, lineNum);

            G(); //predict G

            if (tk.tokenID == T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    tk = scanner(file, lineNum);

                    return; // end of production rule
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
}

//<E> -> ]<K>~
void E()
{
    if (tk.tokenID == T2_token)
    {
        if (tk.tokenInstance == "]")
        {
            tk = scanner(file, lineNum);

            K(); //predict K

            if (tk.tokenID == T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    tk = scanner(file, lineNum);

                    return; // end of production rule
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
}

//<D> -> [t1
void D()
{
    if (tk.tokenID == T2_token) //predict T2
    {
        if (tk.tokenInstance == "[") //predict [
        {
            tk = scanner(file, lineNum);

            if (tk.tokenID == T1_tk) //predict T1
            {
                tk = scanner(file, lineNum);

                return;
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
}

//<C> -> *<K>
void C()
{
    if (tk.tokenID == T2_token)//* is a T2 token
    {
        if (tk.tokenInstance == "*")
        {
            tk = scanner(file, lineNum);

            K(); //predicting K

            return; // end of production rule
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
}

//<L> -> <D>~ || <E>~ || <F>~ || empty
void L()
{
    //first check for T2 token (first sets for non terms are all t2 tokens
    if (tk.tokenID == T2_token)
    {
        //check which instance it is which will decide which rule to follow
        if (tk.tokenInstance == "[") // choose D path
        {
            D(); // predict D

            if (tk.tokenID = T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    tk = scanner(file, lineNum);

                    return; //end of rule
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
            E(); //predict E

            if (tk.tokenID = T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    tk = scanner(file, lineNum);

                    return; //end of rule
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
            F(); //predict f

            if (tk.tokenID = T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    tk = scanner(file, lineNum);

                    return; //end of rule
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
        return; //empty?
    }
}


void J()
{
    //first check for t1 or t2 in current token if not one of these we are in empty case
    if (tk.tokenID == T2_token) //its one of the first few rules
    {
        if (tk.tokenInstance == "*") //process C rule
        {
            C(); //predict C

            if (tk.tokenID == T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    tk = scanner(file, lineNum);

                    J(); //predict J

                    if (tk.tokenID == T2_token)
                    {
                        if (tk.tokenInstance == "~")
                        {
                            tk = scanner(file, lineNum);

                            L(); //predict L

                            return; //end of production rule 1
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
            D(); //predict D

            if (tk.tokenID == T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    tk = scanner(file, lineNum);

                    J(); //predict J

                    return; //end of production 2
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
            E(); //predict E

            if (tk.tokenID == T2_token)
            {
                if (tk.tokenInstance == "~")
                {
                    tk = scanner(file, lineNum);

                    J(); //predict J

                    return; //end of rule 3
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
        F(); //predict F

        if (tk.tokenID == T2_token)
        {
            if (tk.tokenInstance == "~")
            {
                tk = scanner(file, lineNum); //consume

                J(); //predict J

                return; //end of rule 4
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
        return; //empty?
    }
}

//A -> ^t1<A> || empty
void A()
{
    if (tk.tokenID == T2_token) //^ is a t2 token
    {
        if (tk.tokenInstance == "^") //make sure it is the expected ^
        {
            tk = scanner(file, lineNum);

            if (tk.tokenID == T1_tk)
            {
                tk = scanner(file, lineNum);

                A(); //predicting A

                return;
            }
        }
        else
        {
            error();// ^ was the expected terminal so output error.
        }
    }
    else
    {
        return; //empty
    }

}


// <S> -> <S> -> <A><J>
void S()
{
    A(); //predicting A

    J(); //predicting J

    return; //end of production

}


void parser(fstream &file)
{
    tk = scanner(file, lineNum);

    S(); //start with starting nonTerm S

    if (tk.tokenID == EOF_token)
        cout << "Parse Success";
    else
        error();

    return;
}
