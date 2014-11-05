#!/usr/bin/perl

sub gen {
    my $n = shift;
    my @a;
    for(1..$n) {
        if (rand() < 0.1) {
            push @a, $_;
        }
    }
    return @a;
}

my $n = 1000;
my $k = 1000;
print "$n $k\n";
for(1..$k) {
    my @a = gen($n);
    print scalar @a, " ";
    print "@a ";
    if (rand() < 0.5) {
        print "Girl\n"; 
    } else {
        print "Gops\n";
    }
}
