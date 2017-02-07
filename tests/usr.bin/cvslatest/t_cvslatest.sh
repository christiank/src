# $NetBSD$

atf_test_case usage
usage_head() {
	atf_set "descr" "insist the user provides a valid path"
}
usage_body() {
	atf_check -s not-exit:0 -o ignore -e match:Usage \
		cvslatest 

	atf_check -s not-exit:0 -o ignore -e ignore \
		cvslatest /dev/null

	atf_check -s not-exit:0 -o ignore -e ignore \
		cvslatest /a/b/c/nonexistent-directory/d/e/f

	atf_check -s not-exit:0 -o ignore -e ignore \
		cvslatest /etc/rc.conf
}

atf_test_case malformed
malformed_head() {
	atf_set "descr" "complain about malformed Entries files"
}
malformed_body() {
	atf_check -s exit:0 -o ignore -e ignore \
		echo 
}

atf_init_test_cases() {
	atf_add_test_case usage
	atf_add_test_case malformed
}
