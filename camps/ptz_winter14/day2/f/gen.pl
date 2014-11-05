use warnings;
use strict;

sub uniform {
    my $x = shift;
    return int (rand() * $x);
};

my $n = int shift;
my $c = int shift;

print "$n\n";
for (1..$n) {
    printf "%d ", uniform(2*$c) - $c;
}
print "\n";
