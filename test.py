from subprocess import run, PIPE
from termcolor import colored
from sys import exit

testscenario1 = [{'in':'abc/*def*/ghi\n','out':'abc ghi\n'},
 {'in':'abc/*def*/ ghi\n','out':'abc  ghi\n'},
 {'in':'abc /*def*/ghi\n','out': 'abc  ghi\n' }]
testscenario2 = [{'in':'abc//def\n','out':'abc//def\n'}]
testscenario3 = [{'in':'abc/*def\nghi*/jkl\nmno\n','out':'abc jkl\nmno\n'},
{'in':'abc/*def\nghi\njkl*/mno\npqr\n','out':'abc mno\npqr\n'},
{'in':'abc/*def/*ghi*/jkl*/mno\n','out':'abc jkl*/mno\n'}]
testscenario4 = [{'in':'abc/*def/*ghi*/jkl*/mno\n','out':'abc jkl*/mno\n'}]
testscenario5 = [{'in':'abc"def/*ghi*/jkl"mno\n','out':'abc"def/*ghi*/jkl"mno\n'},
{'in':'abc/*def"ghi"jkl*/mno\n','out':'abc mno\n'},
{'in':'abc/*def"ghijkl*/mno\n','out':'abc mno\n'},
{'in':"abc'def/*ghi*/jkl'mno\n",'out':"abc'def/*ghi*/jkl'mno\n"},
{'in':"abc/*def'ghi'jkl*/mno\n",'out':'abc mno\n'},
{'in':"abc/*def'ghijkl*/mno\n",'out':'abc mno\n'}]
testscenario6 = [{'in':'abc"def\"ghi"jkl\n','out':'abc"def\"ghi"jkl\n'},
{'in':'abc"def\'ghi"jkl\n','out':'abc"def\'ghi"jkl\n'}]
testscenario7 = [{'in':"abc'def\'ghi'jkl\n",'out':"abc'def\'ghi'jkl\n"},
{'in':"abc'def\"ghi'jkl\n",'out':"abc'def\"ghi'jkl\n"}]
testscenario8 = [{'in':'abc"def\nghi"jkl\n','out':'abc"def\nghi"jkl\n'},
{'in':'abc"def\nghi\njkl"mno/*pqr*/stu\n','out':'abc"def\nghi\njkl"mno stu\n'},
{'in':"abc'def\nghi'jkl\n",'out':"abc'def\nghi'jkl\n"},
{'in':"abc'def\nghi\njkl'mno/*pqr*/stu\n",'out':"abc'def\nghi\njkl'mno stu\n"}]
testscenario9 = [{'in':'abc"def/*ghi*/jkl\n','out':'abc"def/*ghi*/jkl\n'},
{'in':"abc'def/*ghi*/jkl\n",'out':"abc'def/*ghi*/jkl\n"}]


tests = {'Your program should replace each comment with a space':testscenario1,
'Your program should not consider text of the form ( //... ) to be a comment':testscenario2,
'Your program should allow a comment to span multiple lines':testscenario3,
'Your program should not recognize nested comments':testscenario4,
'Your program should handle C string literals':testscenario5,
'Your program should handle escaped characters within string literals':testscenario6,
'Your program should handle escaped characters within character literals':testscenario7,
'Your program should handle newline characters in C string literals':testscenario8,
'Your program should handle unterminated string and character literals':testscenario9}

failed = 0
passed = 0
total =  0

for k1,scenario in enumerate(tests):
    print('TEST SCENARIO',k1+1,':', scenario)
    for k2,case in enumerate(tests[scenario]):
        p = run(['./decomment'], stdout=PIPE,input=case['in'], encoding='ascii')
        testcase ="\t {} : {}"
        if p.stdout == case['out']:
            print(colored(testcase.format(k2+1,'PASS'),'green'))
            passed+=1
        else:
            print(colored(testcase.format(k2+1,'FAIL'),'red'))
            print(colored("EXPECTED:\n{}\nACTUAL RESULT:\n{}\n".format(case['out'],p.stdout),'red'))

            failed+=1
        total+=1


print("RESULT \nPASSED:{}, FAILED:{}, TOTAL:{}".format(passed,failed,total));
