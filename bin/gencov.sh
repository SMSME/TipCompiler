#!/bin/bash

# Set ROOT_DIR to GITHUB_WORKSPACE or the top-level Git directory
ROOT_DIR=${GITHUB_WORKSPACE:-$(git rev-parse --show-toplevel)}
COV_OUTPUT="${ROOT_DIR}/coverage.info"
HTML_OUTPUT="${ROOT_DIR}/coverage.out"

# Ensure your program is compiled with coverage flags
# Add these flags to your compilation:
# CXXFLAGS="-fprofile-arcs -ftest-coverage"
# LDFLAGS="-lgcov --coverage"

# Clean any existing coverage data
find "${ROOT_DIR}" -name "*.gcda" -delete
find "${ROOT_DIR}" -name "*.gcno" -delete

# [At this point, you need to run your tests/program]
# ./your_test_program

# Check if any .gcda files were generated
if [ -z "$(find ${ROOT_DIR} -name '*.gcda')" ]; then
    echo "Error: No coverage data (.gcda files) found!"
    echo "Make sure to:"
    echo "1. Compile with coverage flags (-fprofile-arcs -ftest-coverage)"
    echo "2. Run your tests/program before generating coverage"
    exit 1
fi

# Capture coverage data
lcov --capture \
     --directory "${ROOT_DIR}" \
     --no-external \
     --output-file "${COV_OUTPUT}" \
     --rc lcov_branch_coverage=1

if [ $? -ne 0 ]; then
    echo "Error: Failed to capture coverage data"
    exit 1
fi

# Remove unwanted coverage data
lcov --remove "${COV_OUTPUT}" \
     "${ROOT_DIR}/build/*" \
     "${ROOT_DIR}/externals/*" \
     '*.h' '*.hpp' \
     -o "${COV_OUTPUT}" \
     --rc lcov_branch_coverage=1

# Generate HTML report
genhtml "${COV_OUTPUT}" \
        --output-directory "${HTML_OUTPUT}" \
        --branch-coverage \
        --function-coverage

echo "Coverage report has been generated as ${COV_OUTPUT}"
echo "An HTML view of this report is available in ${HTML_OUTPUT}"