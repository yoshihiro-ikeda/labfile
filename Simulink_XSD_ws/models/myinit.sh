#!/bin/sh

mdlname=$1

echo $mdlname

if test $# -eq 0
then
echo "Warning! Invalid argument\n" 
exit 1
fi

read -p "startup init?(use rtw_test)y/n:" str
if test $str = "y"
then
    cp ../../SimulinkModel.xsd .
    cp "$mdlname"_ert_rtw/*.c .
    cp "$mdlname"_ert_rtw/*.h .
    if test -e "$mdlname"_data.c
    then
	../../rtw_test -c "$mdlname".c -d "$mdlname"_data.c -h "$mdlname".h "$mdlname".xml out_"$mdlname".xml
	echo "myinit.sh: execute rtw_test with **_data.c"
    else
	../../rtw_test -c "$mdlname".c -h "$mdlname".h "$mdlname".xml out_"$mdlname".xml
	echo "myinit.sh: execute rtw_test without data.c"
    fi
fi

read -p "execute blxmlperf? y/n:" str
if test $str = "y"
then
    ln -s ../../blxml2code .
    ln -s ../../llvm-BLXMLPerf.so .
    ../../blxml-perf.sh -o perf.xml -shim=../../renesas.mcg4p_8core.1_0_0.gcc.4_6_2.xml out_"$mdlname".xml
fi

