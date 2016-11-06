judge(){
    problem="$1";
    g++ $problem.cpp;
    [ $? -ne 0  ] && echo "Could not compile $problem." && return;
    for i in $(ls | grep $problem.*.in); do ./a.out < $i > mine && diff ${i%.*}.ok mine; [ $? -ne 0 ] && echo "TESTCASE $i FAILED!" ; done
}
