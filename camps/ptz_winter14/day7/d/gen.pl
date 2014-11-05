#!/usr/bin/perl

my $n = 35000;
my $m = 35000;
print "$n $m 0\n";
for(1..$n) {
    print "0 0 $_ 0\n";
}
for(1..$m) {
    print "0 0 1\n";
}
