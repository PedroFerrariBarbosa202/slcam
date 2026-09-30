/*
 * errno_test.c
 * 
 * copyright the slcam contributors.
 * 
 * this file is part of slcam.
 * 
 * slcam is free software: you can redistribute it and/or modify
 * it under the terms of the gnu general public license as published by
 * the free software foundation, either version 3 of the license, or
 * (at your option) any later version.
 * 
 * slcam is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose. see the
 * gnu general public license for more details.
 * 
 * you should have received a copy of the gnu general public license
 * along with slcam. if not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief unit test of the errno protocol.
 * 
 * \author gabriel mariano marcelino <gabriel.mm8@gmail.com>
 * \author pedro ferrari barbosa <pedro.ferraribarbosa2007@gmail.com> 
 *
 * \version 0.9.13
 * 
 * \date 2021/09/01
 * 
 * \defgroup errno_unit_test errno
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include <stdlib.h>
#include <math.h>

#include <config/errno.h>

static error_t return_error(int val){
  return (error_t)val;
}

static void check_errno_test(void **state){
  assert_int_equal(return_error(1), ERROR_DRIVER_NO_PORT);
}

static void errno_get_string_test(void** state){
  error_t error = ERROR_DRIVER_FAILED;
  assert_string_equal(error_as_string(error), "ERROR_DRIVER_FAILED");
}

int main(void)
{
    const struct CMUnitTest errno_tests[] = {
        cmocka_unit_test(errno_get_string_test),
        cmocka_unit_test(check_errno_test)
    };

    return cmocka_run_group_tests(errno_tests, NULL, NULL);
}
/** \} end of errno_unit_test group */

