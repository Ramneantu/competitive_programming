judge(){
    problem="$1";
    g++ $problem.cpp;
    [ $? -ne 0  ] && echo "Could not compile $problem." && return;
    for i in $(ls | grep $problem.*.in); do ./a.out < $i > mine; [ ! -e ${i%.*}.ok ] && echo "OK file for TESTCASE $i is missing. Skipping TESTCASE $i" && continue; diff ${i%.*}.ok mine; [ $? -ne 0 ] && echo "TESTCASE $i FAILED!" ; done

    echo "PASSED!";
}
