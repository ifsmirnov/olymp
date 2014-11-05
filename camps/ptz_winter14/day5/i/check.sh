for((i=0;i<100;++i)); do
    perl gen.pl 2000 100000 > input.txt
    if ! ./i; then
        echo "FAIL"
        break
    fi
done
