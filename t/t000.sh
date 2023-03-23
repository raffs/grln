#!/bin/bash

. lib

test_expect_success "It should run" "
        echo hello world | grln
"

test_expect_success "-v | --version should show version" "
        grln --version > out
	grep '^version: v.*' out

	grln -v > out
	grep '^version: v.*' out
"

test_expect_failure "fail when arguments" "
        grln --failed
"
