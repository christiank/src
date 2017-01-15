# $NetBSD$

atf_test_case usage
usage_head() {
	atf_set "descr" "Ensure db(1) called with no arguments yields usage message"
}
usage_body() {
	atf_check -s ignore -o ignore -e not-empty db
}

atf_test_case write_hash cleanup
write_hash_head() {
	atf_set "descr" "Ensure db(1) can create a hash(3) database"
}
write_hash_body() {
	dbname=$(mktemp /tmp/t_db.XXXXXX)
	atf_check -s exit:0 -o match:"Added" -e ignore \
	    db -w hash ${dbname} a b
}
write_hash_cleanup() {
	rm -f ${dbname}
}

atf_test_case update_hash cleanup
update_hash_head() {
	atf_set "descr" \
	    "Ensure db(1) can update a hash(3) database only on purpose" 
}
update_hash_body() {
	key="a"
	old_value="b"
	new_value="c"
	dbname=$(mktemp /tmp/t_db.XXXXXX)

	atf_check -s exit:0 -o ignore -e ignore \
		db -w hash ${dbname} ${key} ${old_value}
	atf_check -s not-exit:0 -o ignore -e ignore \
		db -w hash ${dbname} ${key} ${new_value}
	atf_check -s exit:0 -o ignore -e ignore \
		db -wR hash ${dbname} ${key} ${new_value}
}
update_hash_cleanup() {
	rm -f ${dbname}
}

atf_test_case read_hash cleanup
read_hash_head() {
	atf_set "descr" \
    	    "Ensure db(1) can report the appropriate value for a key in a hash(3) database"
}
read_hash_body() {
	dbname=$(mktemp /tmp/t_db.XXXXXX)
	key="a"
	value="b"

	atf_check -s exit:0 -o ignore -e ignore \
		db -w hash ${dbname} ${key} ${value}
	atf_check -s exit:0 -o match:${value} -e ignore \
		db hash ${dbname} ${key}
}
read_hash_cleanup() {
	rm -f ${dbname}
}

atf_test_case read_hash_quietly cleanup
read_hash_quietly_head() {
	atf_set "descr" \
	    "Ensure db(1) exits (un)successfully depending on quiet mode for hash(3) databases"
}
read_hash_quietly_body() {
	dbname=$(mktemp /tmp/t_db.XXXXXX)
	valid_key="a"
	invalid_key="b"
	value="c"

	atf_check -s exit:0 -o ignore -e ignore \
		db -w hash ${dbname} ${valid_key} ${value}
	atf_check -s not-exit:0 -o ignore -e ignore \
		db hash ${dbname} ${invalid_key}
	atf_check -s exit:0 -o ignore -e ignore \
		db -q hash ${dbname} ${invalid_key}
}
read_hash_quietly_cleanup() {
	rm -f ${dbname}
}

atf_test_case delete_hash cleanup
delete_hash_head() {
	atf_set "descr" \
	    "Ensure db(1) can delete keys in hash(3) databases"
}
delete_hash_body() {
	dbname=$(mktemp /tmp/t_db.XXXXXX)
	valid_key="a"
	invalid_key="b"
	value="c"

	db -w hash ${dbname} ${valid_key} ${value}

	atf_check -s exit:0 -o ignore -e ignore \
		db -d hash ${dbname} ${valid_key}
	atf_check -s not-exit:0 -o ignore -e ignore \
		db -d hash ${dbname} ${valid_key}
	atf_check -s not-exit:0 -o ignore -e ignore \
		db -d hash ${dbname} ${invalid_key}
}
delete_hash_cleanup() {
	rm -f ${dbname}
}

atf_init_test_cases() {
	atf_add_test_case usage
	atf_add_test_case write_hash
	atf_add_test_case update_hash
	atf_add_test_case read_hash
	atf_add_test_case read_hash_quietly
	atf_add_test_case delete_hash
}
