./bin/smake

cd tests/empty_project || exit 1

if [ "$?" = 0 ]; then
    exit 0;
fi

exit 1;