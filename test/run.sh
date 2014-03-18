#!/bin/sh

TESTS=`find test/test-* -type f -perm +111`
EXIT_CODE=0

for t in $TESTS; do
    ./$t
    if [ $? -ne 0 ]; then
        echo >&2 " ✖ $t"
        EXIT_CODE=1
    else
        echo " ✓ $t"
    fi
done

exit $EXIT_CODE
