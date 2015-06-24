
make
./xas yello.xas yello.xo
./xas hello.xas hello.xo
./xas zello.xas zello.xo
./xas goodbye.xas goodbye.xo
./xas kernel.xas kernel.xo
./xas yes.xas yes.xo
./xmkos xos  kernel.xo hello.xo goodbye.xo yello.xo zello.xo 
./xsim 100000 xos 1000 > test.out
./xmkos gold kernel_gold.xo hello.xo goodbye.xo yello.xo zello.xo
./xsim_gold 100000 gold 1000 > test.out.gold
diff test.out test.out.gold > result



