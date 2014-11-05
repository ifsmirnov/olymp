sub uniform {
    my ($a, $b) = map int, @_;
    return $a + int (rand() * ($b - $a + 1));
}

my $n = int shift;
my $c = int shift;
print "$n\n";
for(1..$n) {
    print uniform(1, $c), " ", uniform(1, $c), "\n";
}
