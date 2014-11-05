#!/usr/bin/perl

sub uniform {
    my ($a, $b) = map int, @_;
    return $a + int (rand() * ($b-$a+1));
}

my $n = shift;
print $n, "\n";
for(1..$n) {
    print chr uniform(100,102) for (1..5);
    print "\n";
}
