Ceci est un test

0: PROMPT

1: LEXER
    Analyse lexicale des arguments fournis.

2: PARSER
    Decoupage des commandes

3: EXECUTOR
    Executer les commandes fournies

4: TOKEN
    1: < should redirect input.
    2: > should redirect output.
    3: << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
    4: >> should redirect output in append mode.

5: BUILT IN
    1: ECHO
        1BIS: -n
    2: CD
    3: PWD
    4: EXPORT
    5: UNSET
    6: ENV
    7: EXIT

6: SIGNAUX
    1: ctrl-C displays a new prompt on a new line.
    2: ctrl-D exits the shell.
    3: ctrl-\ does nothing.

7: HISTORIQUE