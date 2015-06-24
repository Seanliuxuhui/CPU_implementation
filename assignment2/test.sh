./xas test.sim.02.xas test.sim.02.xo 
./xsim_gold 10000 test.sim.02.xo 0 > test.sim.02.out
./xsim 10000 test.sim.02.xo 0 > test.sim.02
diff test.sim.02 test.sim.02.gold > result2

./xas test.sim.01.xas test.sim.01.xo
./xsim_gold 10000 test.sim.01.xo 0 > test.sim.01.out
./xsim 10000 test.sim.01.xo 0 > test.sim.01
diff test.sim.01 test.sim.01.gold > result1

./xas test.sim.03.xas test.sim.03.xo
./xsim_gold 10000 test.sim.03.xo 0 > test.sim.03.out
./xsim 10000 test.sim.03.xo 0 > test.sim.03
diff test.sim.03 test.sim.03.gold > result3

./xas test.sim.04.xas test.sim.04.xo
./xsim_gold 10000 test.sim.04.xo 0 > test.sim.04.out
./xsim 10000 test.sim.04.xo 0 > test.sim.04
diff test.sim.04 test.sim.04.gold > result4

./xas test.sim.05.xas test.sim.05.xo
./xsim_gold 10000 test.sim.05.xo 0 > test.sim.05.out
./xsim 10000 test.sim.05.xo 0 > test.sim.05
diff test.sim.05 test.sim.05.gold > result5

./xas test.sim.06.xas test.sim.06.xo
./xsim_gold 10000 test.sim.06.xo 0 > test.sim.06.out
./xsim 10000 test.sim.06.xo 0 > test.sim.06
diff test.sim.06 test.sim.06.gold > result6

./xas test.sim.07.xas test.sim.07.xo
./xsim_gold 10000 test.sim.07.xo 0 > test.sim.07.out
./xsim 10000 test.sim.07.xo 0 > test.sim.07
diff test.sim.07 test.sim.07.gold > result7

./xas test.sim.08.xas test.sim.08.xo
./xsim_gold 10000 test.sim.08.xo 0 > test.sim.08.out
./xsim 10000 test.sim.08.xo 0 > test.sim.08
diff test.sim.08 test.sim.08.gold > result8

./xas test.sim.09.xas test.sim.09.xo
./xsim_gold 10000 test.sim.09.xo 0 > test.sim.09.out
./xsim 10000 test.sim.09.xo 0 > test.sim.09
diff test.sim.09 test.sim.09.gold > result9

./xas test.sim.10.xas test.sim.10.xo
./xsim_gold 10000 test.sim.10.xo 0 > test.sim.10.out
./xsim 10000 test.sim.10.xo 0 > test.sim.10
diff test.sim.10 test.sim.10.gold > result10


./xas kernel.xas kernel.xo
./xas test.A.xas test.A.xo
./xas test.B.xas test.B.xo
./xmkos int_two kernel.xo test.A.xo test.B.xo 
./xmkos int_two_gold kernel_gold.xo test.A.xo test.B.xo
./xsim_gold 100000 int_two_gold 1000 > test.int.out
./xsim 100000 int_two 1000 > test.int.out.gold
diff test.int.out.gold test.int.out > int_two_result


./xmkos xos kernel.xo hello.xo yello.xo zello.xo goodbye.xo 
./xsim_gold 100000 xos 1000 > test.trap.out
mv test.sim.01.gold test.sim.01.txt
mv test.sim.02.gold test.sim.02.txt
mv test.sim.03.gold test.sim.03.txt
mv test.sim.04.gold test.sim.04.txt
mv test.sim.05.gold test.sim.05.txt
mv test.sim.06.gold test.sim.06.txt
mv test.sim.07.gold test.sim.07.txt
mv test.sim.08.gold test.sim.08.txt
mv test.sim.09.gold test.sim.09.txt
mv test.sim.10.gold test.sim.10.txt
