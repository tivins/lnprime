
libln_dir=libln
base_objs=obj/$(libln_dir)/src/ln_debug.o obj/$(libln_dir)/src/prime_debug.o obj/lib/util_debug.o
base_objs_release=obj/$(libln_dir)/src/ln_release.o obj/$(libln_dir)/src/prime_release.o obj/lib/util_release.o
tests_objs=obj/$(libln_dir)/tests/test_ln_sqrt_debug.o \
	obj/$(libln_dir)/tests/test_ln_copy_debug.o \
	obj/$(libln_dir)/tests/test_ln_pow_debug.o
libdir=-Isrc/$(libln_dir)/src


all: lnprime_debug lnprime lnpow_debug lnpow minimal tests

minimal: $(base_objs) obj/minimal_debug.o
	gcc -pg -O0 -Wall --pedantic -o $@ $^

tests: $(base_objs)  $(tests_objs)
	gcc -pg -O0 -Wall --pedantic -o test_ln_sqrt $(base_objs) obj/$(libln_dir)/tests/test_ln_sqrt_debug.o
	gcc -pg -O0 -Wall --pedantic -o test_ln_copy $(base_objs) obj/$(libln_dir)/tests/test_ln_copy_debug.o
	gcc -pg -O0 -Wall --pedantic -o test_ln_pow $(base_objs) obj/$(libln_dir)/tests/test_ln_pow_debug.o

lnprime_debug: $(base_objs) obj/lnprime_debug.o
	gcc -pg -O0 -Wall --pedantic -o $@ $^

lnprime: $(base_objs_release) obj/lnprime_release.o
	gcc -O3 -o $@ $^

lnpow_debug: $(base_objs) obj/lnpow_debug.o
	gcc -pg -O0 -Wall --pedantic -o $@ $^

lnpow: $(base_objs_release) obj/lnpow_release.o
	gcc -O3 -o $@ $^

obj/%_debug.o: src/%.c
	dirname $@ | xargs mkdir -p
	gcc $(libdir) -pg -O0 -Wall --pedantic -c $^ -o $@

obj/%_release.o: src/%.c
	dirname $@ | xargs mkdir -p
	gcc $(libdir) -O3 -c $^ -o $@

clean:
	$(RM) -r obj/
	$(RM) gmon.out

proper: clean
	$(RM) lnprime_release lnprime_debug minimal test_ln_sqrt test_ln_copy test_ln_pow

check:
	valgrind --leak-check=full --track-origins=yes --leak-check=yes $(PROG)
