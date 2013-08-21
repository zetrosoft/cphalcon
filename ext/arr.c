
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2013 Phalcon Team (http://www.phalconphp.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@phalconphp.com so we can send you a copy immediately.       |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
  |          Eduar Carvajal <eduar@phalconphp.com>                         |
  |          ZhuZongXin <dreamsxin@qq.com>                                 |
  |          Vladimir Kolesnikov <vladimir@free-sevastopol.com>            |
  +------------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_phalcon.h"
#include "phalcon.h"

#include "Zend/zend_operators.h"
#include "Zend/zend_exceptions.h"
#include "Zend/zend_interfaces.h"

#include "kernel/main.h"
#include "kernel/memory.h"

#include "kernel/exception.h"
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/hash.h"
#include "kernel/concat.h"
#include "kernel/operators.h"
#include "kernel/string.h"

/**
 * Phalcon\Arr
 *
 * Phalcon\Arr is array helper.
 * This component is an abstract class that you can extend to add more helpers.
 */


/**
 * Phalcon\Arr initializer
 */
PHALCON_INIT_CLASS(Phalcon_Arr){

	PHALCON_REGISTER_CLASS(Phalcon, Arr, arr, phalcon_arr_method_entry, 0);

	zend_declare_property_string(phalcon_arr_ce, SL("delimiter"), ".", ZEND_ACC_PUBLIC|ZEND_ACC_STATIC TSRMLS_CC);

	return SUCCESS;
}

/**
 * Tests if an array is associative or not.
 *
 *     // Returns TRUE
 *     \Phalcon\Arr::is_assoc(array('username' => 'john.doe'))
 *
 * @param array $array
 * @return boolean
 */
PHP_METHOD(Phalcon_Arr, is_assoc){

	zval *array;

	phalcon_fetch_params(0, 1, 0, &array);
	
	if (phalcon_array_is_associative(array)) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}

/**
 * Test if a value is an array with an additional check for array-like objects.
 *
 *     // Returns TRUE
 *     Arr::is_array(array());
 *
 * @param mixed $value
 * @return boolean
 */
PHP_METHOD(Phalcon_Arr, is_array){

	zval *value, *is_traversable;
	zend_class_entry *ce;

	PHALCON_MM_GROW();

	phalcon_fetch_params(1, 1, 0, &value);

	if (Z_TYPE_P(value) == IS_ARRAY) {
		RETURN_MM_TRUE;
	} else if (Z_TYPE_P(value) == IS_OBJECT) {
		ce = zend_fetch_class(SL("Traversable"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);

		PHALCON_INIT_VAR(is_traversable);
		phalcon_instance_of(is_traversable, value, ce TSRMLS_CC);

		if (zend_is_true(is_traversable)) {
			RETURN_MM_TRUE;
		}
		RETURN_MM_FALSE;
	} else {
		RETURN_MM_FALSE;
	}
}

/**
 * Gets a value from an array using a dot separated path.
 *
 *     // Get the value of $array['foo']['bar']
 *     $value = Arr::path($array, 'foo.bar');
 *
 * Using a wildcard "*" will search intermediate arrays and return an array.
 *
 *     // Get the values of "color" in theme
 *     $colors = Arr::path($array, 'theme.*.color');
 *
 *     // Using an array of keys
 *     $colors = Arr::path($array, array('theme', '*', 'color'));
 *
 * @param array $array
 * @param mixed $path
 * @param mixed $default
 * @param string $delimiter
 * @return mixed
 */
PHP_METHOD(Phalcon_Arr, path){

	zval *array, *path, *default_value = NULL, *delimiter = NULL;
	zval *is_array, *keys, *key = NULL, *values = NULL, *is_digit = NULL, *arr = NULL, *value = NULL, *joined_keys = NULL;
	HashTable *ah0;
	HashPosition hp0;
	zval **hd;
	int c, i;

	PHALCON_MM_GROW();

	phalcon_fetch_params(1, 2, 2, &array, &path, &default_value, &delimiter);

	PHALCON_INIT_VAR(is_array);
	phalcon_call_self_p1(is_array, this_ptr, "is_array", array);
	if (!zend_is_true(is_array)) {
		goto end;
	}

	if (Z_TYPE_P(path) == IS_ARRAY) {
		PHALCON_CPY_WRT(keys, path);
	} else {
		if (phalcon_array_isset_fetch(&values, array, path)) {
			RETURN_ZVAL(values, 1, 0);
		}

		if (!delimiter) {
			PHALCON_INIT_VAR(delimiter);
			phalcon_read_static_property(&delimiter, SL("phalcon\\arr"), SL("delimiter") TSRMLS_CC);
		}

		phalcon_fast_explode(keys, delimiter, path);
	}

	do {
		PHALCON_INIT_NVAR(key);
		phalcon_call_func_p1(key, "array_shift", keys);

		if (Z_TYPE_P(key) == IS_NULL) {
			break;
		}

		PHALCON_INIT_NVAR(is_digit);
		phalcon_call_func_p1(is_digit, "ctype_digit", key);
	
		if (zend_is_true(is_digit)) {
			convert_to_long(key);
		}
		
		if (phalcon_array_isset_fetch(&values, array, key)) {
			if ((i + 1) < c) {
				PHALCON_INIT_NVAR(is_array);
				phalcon_call_self_p1(is_array, this_ptr, "is_array", values);
				if (zend_is_true(is_array)) {
					PHALCON_CPY_WRT(array, values);
				} else {
					// Unable to dig deeper
					break;
				}
			} else {
				RETURN_CCTOR(values);
			}
		} else if (PHALCON_IS_STRING(key, "*")) {
			PHALCON_INIT_NVAR(values);
			array_init(values);
			
			phalcon_is_iterable(array, &ah0, &hp0, 0, 0);

			while (zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) == SUCCESS) {
				PHALCON_GET_HVALUE(arr);

				PHALCON_INIT_NVAR(joined_keys);
				phalcon_fast_join_str(joined_keys, SL("."), keys TSRMLS_CC);

				PHALCON_INIT_NVAR(value);
				phalcon_call_self_p1(value, this_ptr, "path", arr);

				if (Z_TYPE_P(value) != IS_NULL) {
					phalcon_array_append(&values, value, 0);
				}

				zend_hash_move_forward_ex(ah0, &hp0);
			}

			if (phalcon_fast_count_ev(values TSRMLS_CC)) {
				// Found the values requested
				RETURN_CCTOR(values);
			} else {
				// Unable to dig deeper
				break;
			}
		} else {
			// Unable to dig deeper
			break;
		}
	} while (phalcon_fast_count_ev(keys TSRMLS_CC));

end:
	if (default_value) {
		RETURN_CTOR(default_value);
	}

	RETURN_MM_NULL();
}

/**
 * Set a value on an array by path.
 *
 * @see Arr::path()
 * @param array $array
 * @param string $path
 * @param mixed $value
 * @param string $delimiter
 */
PHP_METHOD(Phalcon_Arr, set_path){

	zval *array, *path, *value, *delimiter;
	zval *keys, *key = NULL, *is_digit = NULL, *arr, *tmp;
	zend_class_entry *ce;

	PHALCON_MM_GROW();

	phalcon_fetch_params(1, 3, 1, &array, &path, &value, &delimiter);

	if (!delimiter) {
		PHALCON_INIT_VAR(delimiter);
		phalcon_read_static_property(&delimiter, SL("phalcon\\arr"), SL("delimiter") TSRMLS_CC);
	}

	// Split the keys by delimiter
	phalcon_fast_explode(keys, delimiter, path);

	PHALCON_INIT_VAR(arr);
	array_init(arr);

	// Set current $array to inner-most array  path
	while (phalcon_fast_count_ev(keys TSRMLS_CC) > 1) {
		PHALCON_INIT_NVAR(key);
		phalcon_call_func_p1(key, "array_shift", keys);

		PHALCON_INIT_NVAR(is_digit);
		phalcon_call_func_p1(is_digit, "ctype_digit", key);
	
		if (zend_is_true(is_digit)) {
			convert_to_long(key);
		}

		if (!phalcon_array_isset(array, key)) {
			phalcon_array_update_zval(&array, key, &arr, 0);
		}

		if (phalcon_array_isset_fetch(&tmp, array, key)) {
			PHALCON_CPY_WRT(array, tmp);
		}
	}

	PHALCON_INIT_NVAR(key);
	phalcon_call_func_p1(key, "array_shift", keys);

	phalcon_array_update_zval(&array, key, &value, 0);

	PHALCON_MM_RESTORE();
}

/**
 * Fill an array with a range of numbers.
 *
 *     // Fill an array with values 5, 10, 15, 20
 *     $values = Arr::range(5, 20);
 *
 * @param integer $step
 * @param integer $max
 * @return array
 */
 PHP_METHOD(Phalcon_Arr, range){
	PHALCON_MM_GROW();
	PHALCON_MM_RESTORE();
}

/**
 * Retrieve a single key from an array. If the key does not exist in the
 * array, the default value will be returned instead.
 *
 *     // Get the value "username" from $_POST, if it exists
 *     $username = Arr::get($_POST, 'username');
 *
 * @param array $array
 * @param string $key
 * @param mixed $default
 * @return mixed
 */
 PHP_METHOD(Phalcon_Arr, get){
	PHALCON_MM_GROW();
	PHALCON_MM_RESTORE();
}

/**
 * Retrieves multiple paths from an array. If the path does not exist in the
 * array, the default value will be added instead.
 *
 *     // Get the values "username", "password" from $_POST
 *     $auth = Arr::extract($_POST, array('username', 'password'));
 *     
 *     // Get the value "level1.level2a" from $data
 *     $data = array('level1' => array('level2a' => 'value 1', 'level2b' => 'value 2'));
 *     Arr::extract($data, array('level1.level2a', 'password'));
 *
 * @param array $array
 * @param array $paths
 * @param mixed $default
 * @return array
 */
 PHP_METHOD(Phalcon_Arr, extract){
	PHALCON_MM_GROW();
	PHALCON_MM_RESTORE();
}

/**
 * Retrieves muliple single-key values from a list of arrays.
 *
 *     // Get all of the "id" values from a result
 *     $ids = Arr::pluck($result, 'id');
 *
 * @param array $array
 * @param string $key
 * @return array
 */
 PHP_METHOD(Phalcon_Arr, pluck){
	PHALCON_MM_GROW();
	PHALCON_MM_RESTORE();
}

/**
 * Adds a value to the beginning of an associative array.
 *
 *     // Add an empty value to the start of a select list
 *     Arr::unshift($array, 'none', 'Select a value');
 *
 * @param array $array
 * @param string $key
 * @param mixed $val
 * @return array
 */
 PHP_METHOD(Phalcon_Arr, unshift){
	PHALCON_MM_GROW();
	PHALCON_MM_RESTORE();
}

/**
 * Recursive version of [array_map](http://php.net/array_map), applies one or more
 * callbacks to all elements in an array, including sub-arrays.
 *
 *     // Apply "strip_tags" to every element in the array
 *     $array = Arr::map('strip_tags', $array);
 *
 *     // Apply $this->filter to every element in the array
 *     $array = Arr::map(array(array($this,'filter')), $array);
 *
 * @param mixed $callbacks
 * @param array $array
 * @param array $keys
 * @return array
 */
 PHP_METHOD(Phalcon_Arr, map){
	PHALCON_MM_GROW();
	PHALCON_MM_RESTORE();
}

/**
 * Recursively merge two or more arrays. Values in an associative array
 * overwrite previous values with the same key. Values in an indexed array
 * are appended, but only when they do not already exist in the result.
 *
 * Note that this does not work the same as [array_merge_recursive](http://php.net/array_merge_recursive)!
 *
 *     $john = array('name' => 'john', 'children' => array('fred', 'paul', 'sally', 'jane'));
 *     $mary = array('name' => 'mary', 'children' => array('jane'));
 *
 *     // John and Mary are married, merge them together
 *     $john = Arr::merge($john, $mary);
 *
 *     // The output of $john will now be:
 *     array('name' => 'mary', 'children' => array('fred', 'paul', 'sally', 'jane'))
 *
 * @param array $array1
 * @param array $array2,...
 * @return array
 */
 PHP_METHOD(Phalcon_Arr, merge){
	PHALCON_MM_GROW();
	PHALCON_MM_RESTORE();
}

/**
 * Overwrites an array with values from input arrays.
 * Keys that do not exist in the first array will not be added!
 *
 *     $a1 = array('name' => 'john', 'mood' => 'happy', 'food' => 'bacon');
 *     $a2 = array('name' => 'jack', 'food' => 'tacos', 'drink' => 'beer');
 *
 *     // Overwrite the values of $a1 with $a2
 *     $array = Arr::overwrite($a1, $a2);
 *
 *     // The output of $array will now be:
 *     array('name' => 'jack', 'mood' => 'happy', 'food' => 'tacos')
 *
 * @param array $array1
 * @param array $array2
 * @return array
 */
 PHP_METHOD(Phalcon_Arr, overwrite){
	PHALCON_MM_GROW();
	PHALCON_MM_RESTORE();
}

/**
 * Creates a callable function and parameter list from a string representation.
 * Note that this function does not validate the callback string.
 *
 *     // Get the callback function and parameters
 *     list($func, $params) = Arr::callback('Foo::bar(apple,orange)');
 *
 *     // Get the result of the callback
 *     $result = call_user_func_array($func, $params);
 *
 * @param string $str
 * @return array function, params
 */
 PHP_METHOD(Phalcon_Arr, callback){
	PHALCON_MM_GROW();
	PHALCON_MM_RESTORE();
}

/**
 * Convert a multi-dimensional array into a single-dimensional array.
 *
 *     $array = array('set' => array('one' => 'something'), 'two' => 'other');
 *
 *     // Flatten the array
 *     $array = Arr::flatten($array);
 *
 *     // The array will now be
 *     array('one' => 'something', 'two' => 'other');
 *
 * @param array $array
 * @return array
 */
 PHP_METHOD(Phalcon_Arr, flatten){
	PHALCON_MM_GROW();
	PHALCON_MM_RESTORE();
}