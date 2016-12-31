# $NetBSD$

atf_test_case noargs_nonzero
noargs_nonzero_head() {
	atf_set "descr" "Ensure usbhidaction(1) with no arguments exits nonzero"
}
noargs_nonzero_body() {
	atf_check -s not-exit:0 -oignore -eignore usbhidaction
}

atf_test_case noargs_usage
noargs_usage_head() {
	atf_set "descr" "Ensure usbhidaction(1) with no arguments prints usage message"
}
noargs_usage_body() {
	atf_check -s ignore -o not-empty -e not-empty usbhidaction
}

atf_test_case jj
jj_head() {
  atf_set "descr" "xx"
}
jj_body() {
  atf_check -s ignore -o empty -e not-empty usbhidaction -c /dev/null -f uhid0 -v
}

atf_init_test_cases() {
	atf_add_test_case noargs_nonzero
	atf_add_test_case noargs_usage
	atf_add_test_case jj
}
