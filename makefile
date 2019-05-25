
base_objs=obj/ln_debug.o obj/util_debug.o

all: lnprime_debug lnprime_release minimal tests

minimal: obj/ln_debug.o obj/prime_debug.o obj/minimal_debug.o
	gcc -pg -O0 -Wall --pedantic -o $@ $^

tests: $(base_objs) obj/prime_debug.o obj/tests_debug.o obj/tests/test_ln_sqrt_debug.o obj/tests/test_ln_copy_debug.o obj/tests/test_ln_pow_debug.o
	gcc -pg -O0 -Wall --pedantic -o tests $(base_objs) obj/prime_debug.o obj/tests_debug.o
	gcc -pg -O0 -Wall --pedantic -o test_ln_sqrt $(base_objs) obj/tests/test_ln_sqrt_debug.o
	gcc -pg -O0 -Wall --pedantic -o test_ln_copy $(base_objs) obj/tests/test_ln_copy_debug.o
	gcc -pg -O0 -Wall --pedantic -o test_ln_pow $(base_objs) obj/tests/test_ln_pow_debug.o

lnprime_debug: $(base_objs) obj/prime_debug.o obj/main_debug.o
	gcc -pg -O0 -Wall --pedantic -o $@ $^

lnprime_release: obj/ln_release.o obj/util_release.o obj/prime_release.o obj/main_release.o
	gcc -O3 -o $@ $^

obj/%_debug.o: src/%.c
	dirname $@ | xargs mkdir -p
	gcc -pg -O0 -Wall --pedantic -c $^ -o $@

obj/%_release.o: src/%.c
	dirname $@ | xargs mkdir -p
	gcc -O3 -c $^ -o $@

clean:
	$(RM) -r obj/
	$(RM) gmon.out

proper: clean
	$(RM) lnprime_release lnprime_debug minimal tests

check:
	valgrind --leak-check=full --track-origins=yes --leak-check=yes $(PROG)
