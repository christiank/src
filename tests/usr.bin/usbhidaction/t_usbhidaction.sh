# $NetBSD$

atf_test_case noargs
noargs_head() {
	atf_set "descr" "Ensure running w/ no flags returns nonzero"
}
noargs_body() {
	atf_check -s not-exit:0 -oignore -eignore usbhidaction
}

atf_init_test_cases() {
	atf_add_test_case noargs
}
