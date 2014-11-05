#!/usr/bin/perl

use warnings;
use strict;

sub uniform {
    my ($a, $b) = @_;
    return $a + int (rand() * ($b - $a + 1)) + $a;
}

my $n = 50000;
my $c = 30000;
print "$n\n";
print uniform(0, $c), " ", uniform(0, $c), "\n" for (1..$n);
