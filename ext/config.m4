PHP_ARG_ENABLE(phalcon, whether to enable phalcon, [ --enable-phalcon   Enable Phalcon])

if test "$PHP_PHALCON" = "yes"; then
	AC_DEFINE(HAVE_PHALCON, 1, [Whether you have Phalcon])
	phalcon_sources="phalcon.c kernel/main.c kernel/memory.c kernel/exception.c kernel/hash.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/extended/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/alternative/fcall.c kernel/file.c kernel/operators.c kernel/concat.c kernel/variables.c phalcon/acl.c phalcon/acl/adapter.c phalcon/acl/adapter/memory.c phalcon/acl/adapterinterface.c phalcon/acl/exception.c phalcon/acl/resource.c phalcon/acl/resourceinterface.c phalcon/acl/role.c phalcon/acl/roleinterface.c phalcon/annotations/adapter.c phalcon/annotations/adapter/apc.c phalcon/annotations/adapter/files.c phalcon/annotations/adapter/memory.c phalcon/annotations/adapter/xcache.c phalcon/annotations/adapterinterface.c phalcon/annotations/annotation.c phalcon/annotations/collection.c phalcon/annotations/exception.c phalcon/annotations/reader.c phalcon/annotations/readerinterface.c phalcon/annotations/reflection.c phalcon/assets/collection.c phalcon/assets/exception.c phalcon/assets/filterinterface.c phalcon/assets/filters/cssmin.c phalcon/assets/filters/jsmin.c phalcon/assets/filters/none.c phalcon/assets/manager.c phalcon/assets/resource.c phalcon/assets/resource/css.c phalcon/assets/resource/js.c phalcon/cache/backend.c phalcon/cache/backend/apc.c phalcon/cache/backend/file.c phalcon/cache/backend/libmemcached.c phalcon/cache/backend/memcache.c phalcon/cache/backend/memory.c phalcon/cache/backend/mongo.c phalcon/cache/backend/xcache.c phalcon/cache/backendinterface.c phalcon/cache/exception.c phalcon/cache/frontend/base64.c phalcon/cache/frontend/data.c phalcon/cache/frontend/igbinary.c phalcon/cache/frontend/json.c phalcon/cache/frontend/none.c phalcon/cache/frontend/output.c phalcon/cache/frontendinterface.c phalcon/cache/multiple.c phalcon/cli/console.c phalcon/cli/console/exception.c phalcon/cli/dispatcher.c phalcon/cli/dispatcher/exception.c phalcon/cli/router.c phalcon/cli/router/exception.c phalcon/cli/task.c phalcon/config.c phalcon/config/adapter/ini.c phalcon/config/adapter/json.c phalcon/config/exception.c phalcon/crypt.c phalcon/crypt/exception.c phalcon/cryptinterface.c phalcon/db.c phalcon/db/adapter.c phalcon/db/adapter/pdo.c phalcon/db/adapter/pdo/mysql.c phalcon/db/adapter/pdo/oracle.c phalcon/db/adapter/pdo/postgresql.c phalcon/db/adapter/pdo/sqlite.c phalcon/db/adapterinterface.c phalcon/db/column.c phalcon/db/columninterface.c phalcon/db/dialect.c phalcon/db/dialect/mysql.c phalcon/db/dialect/oracle.c phalcon/db/dialect/postgresql.c phalcon/db/dialect/sqlite.c phalcon/db/dialectinterface.c phalcon/db/exception.c phalcon/db/index.c phalcon/db/indexinterface.c phalcon/db/profiler.c phalcon/db/profiler/item.c phalcon/db/rawvalue.c phalcon/db/reference.c phalcon/db/referenceinterface.c phalcon/db/result/pdo.c phalcon/db/resultinterface.c phalcon/debug.c phalcon/di.c phalcon/di/exception.c phalcon/di/factorydefault.c phalcon/di/factorydefault/cli.c phalcon/di/injectable.c phalcon/di/injectionawareinterface.c phalcon/di/service.c phalcon/di/service/builder.c phalcon/di/serviceinterface.c phalcon/diinterface.c phalcon/dispatcher.c phalcon/dispatcherinterface.c phalcon/escaper.c phalcon/escaper/exception.c phalcon/escaperinterface.c phalcon/events/event.c phalcon/events/eventsawareinterface.c phalcon/events/exception.c phalcon/events/manager.c phalcon/events/managerinterface.c phalcon/exception.c phalcon/filter.c phalcon/filter/exception.c phalcon/filter/userfilterinterface.c phalcon/filterinterface.c phalcon/flash.c phalcon/flash/direct.c phalcon/flash/exception.c phalcon/flash/session.c phalcon/flashinterface.c phalcon/forms/element.c phalcon/forms/element/check.c phalcon/forms/element/date.c phalcon/forms/element/email.c phalcon/forms/element/file.c phalcon/forms/element/hidden.c phalcon/forms/element/numeric.c phalcon/forms/element/password.c phalcon/forms/element/select.c phalcon/forms/element/submit.c phalcon/forms/element/text.c phalcon/forms/element/textarea.c phalcon/forms/elementinterface.c phalcon/forms/exception.c phalcon/forms/form.c phalcon/forms/manager.c phalcon/http/cookie.c phalcon/http/cookie/exception.c phalcon/http/request.c phalcon/http/request/exception.c phalcon/http/request/file.c phalcon/http/request/fileinterface.c phalcon/http/requestinterface.c phalcon/http/response.c phalcon/http/response/cookies.c phalcon/http/response/cookiesinterface.c phalcon/http/response/exception.c phalcon/http/response/headers.c phalcon/http/response/headersinterface.c phalcon/http/responseinterface.c phalcon/image.c phalcon/image/adapter.c phalcon/image/adapter/gd.c phalcon/image/adapter/imagick.c phalcon/image/adapterinterface.c phalcon/image/exception.c phalcon/kernel.c phalcon/loader.c phalcon/loader/exception.c phalcon/logger.c phalcon/logger/adapter.c phalcon/logger/adapter/file.c phalcon/logger/adapter/firephp.c phalcon/logger/adapter/stream.c phalcon/logger/adapter/syslog.c phalcon/logger/adapterinterface.c phalcon/logger/exception.c phalcon/logger/formatter.c phalcon/logger/formatter/firephp.c phalcon/logger/formatter/json.c phalcon/logger/formatter/line.c phalcon/logger/formatter/syslog.c phalcon/logger/formatterinterface.c phalcon/logger/item.c phalcon/logger/multiple.c phalcon/mvc/application.c phalcon/mvc/application/exception.c phalcon/mvc/collection.c phalcon/mvc/collection/document.c phalcon/mvc/collection/exception.c phalcon/mvc/collection/manager.c phalcon/mvc/collection/managerinterface.c phalcon/mvc/collectioninterface.c phalcon/mvc/controller.c phalcon/mvc/controllerinterface.c phalcon/mvc/dispatcher.c phalcon/mvc/dispatcher/exception.c phalcon/mvc/dispatcherinterface.c phalcon/mvc/micro.c phalcon/mvc/micro/collection.c phalcon/mvc/micro/collectioninterface.c phalcon/mvc/micro/exception.c phalcon/mvc/micro/lazyloader.c phalcon/mvc/micro/middlewareinterface.c phalcon/mvc/model.c phalcon/mvc/model/behavior.c phalcon/mvc/model/behavior/softdelete.c phalcon/mvc/model/behavior/timestampable.c phalcon/mvc/model/behaviorinterface.c phalcon/mvc/model/criteria.c phalcon/mvc/model/criteriainterface.c phalcon/mvc/model/exception.c phalcon/mvc/model/manager.c phalcon/mvc/model/managerinterface.c phalcon/mvc/model/message.c phalcon/mvc/model/messageinterface.c phalcon/mvc/model/metadata.c phalcon/mvc/model/metadata/apc.c phalcon/mvc/model/metadata/files.c phalcon/mvc/model/metadata/memory.c phalcon/mvc/model/metadata/session.c phalcon/mvc/model/metadata/strategy/annotations.c phalcon/mvc/model/metadata/strategy/introspection.c phalcon/mvc/model/metadata/xcache.c phalcon/mvc/model/metadatainterface.c phalcon/mvc/model/query.c phalcon/mvc/model/query/builder.c phalcon/mvc/model/query/builderinterface.c phalcon/mvc/model/query/lang.c phalcon/mvc/model/query/status.c phalcon/mvc/model/query/statusinterface.c phalcon/mvc/model/queryinterface.c phalcon/mvc/model/relation.c phalcon/mvc/model/relationinterface.c phalcon/mvc/model/resultinterface.c phalcon/mvc/model/resultset.c phalcon/mvc/model/resultset/complex.c phalcon/mvc/model/resultset/simple.c phalcon/mvc/model/resultsetinterface.c phalcon/mvc/model/row.c phalcon/mvc/model/transaction.c phalcon/mvc/model/transaction/exception.c phalcon/mvc/model/transaction/failed.c phalcon/mvc/model/transaction/manager.c phalcon/mvc/model/transaction/managerinterface.c phalcon/mvc/model/transactioninterface.c phalcon/mvc/model/validationfailed.c phalcon/mvc/model/validator.c phalcon/mvc/model/validator/email.c phalcon/mvc/model/validator/exclusionin.c phalcon/mvc/model/validator/inclusionin.c phalcon/mvc/model/validator/numericality.c phalcon/mvc/model/validator/presenceof.c phalcon/mvc/model/validator/regex.c phalcon/mvc/model/validator/stringlength.c phalcon/mvc/model/validator/uniqueness.c phalcon/mvc/model/validator/url.c phalcon/mvc/model/validatorinterface.c phalcon/mvc/modelinterface.c phalcon/mvc/moduledefinitioninterface.c phalcon/mvc/router.c phalcon/mvc/router/annotations.c phalcon/mvc/router/exception.c phalcon/mvc/router/group.c phalcon/mvc/router/route.c phalcon/mvc/router/routeinterface.c phalcon/mvc/routerinterface.c phalcon/mvc/url.c phalcon/mvc/url/exception.c phalcon/mvc/urlinterface.c phalcon/mvc/user/component.c phalcon/mvc/user/module.c phalcon/mvc/user/plugin.c phalcon/mvc/view.c phalcon/mvc/view/engine.c phalcon/mvc/view/engine/php.c phalcon/mvc/view/engine/volt.c phalcon/mvc/view/engine/volt/compiler.c phalcon/mvc/view/engineinterface.c phalcon/mvc/view/exception.c phalcon/mvc/view/simple.c phalcon/mvc/viewinterface.c phalcon/paginator/adapter/model.c phalcon/paginator/adapter/nativearray.c phalcon/paginator/adapter/querybuilder.c phalcon/paginator/adapterinterface.c phalcon/paginator/exception.c phalcon/queue/beanstalk.c phalcon/queue/beanstalk/job.c phalcon/security.c phalcon/security/exception.c phalcon/session.c phalcon/session/adapter.c phalcon/session/adapter/files.c phalcon/session/adapterinterface.c phalcon/session/bag.c phalcon/session/baginterface.c phalcon/session/exception.c phalcon/tag.c phalcon/tag/exception.c phalcon/tag/select.c phalcon/text.c phalcon/translate.c phalcon/translate/adapter.c phalcon/translate/adapter/nativearray.c phalcon/translate/adapterinterface.c phalcon/translate/exception.c phalcon/validation.c phalcon/validation/exception.c phalcon/validation/message.c phalcon/validation/message/group.c phalcon/validation/validator.c phalcon/validation/validator/alnum.c phalcon/validation/validator/alpha.c phalcon/validation/validator/between.c phalcon/validation/validator/confirmation.c phalcon/validation/validator/digit.c phalcon/validation/validator/email.c phalcon/validation/validator/exclusionin.c phalcon/validation/validator/file.c phalcon/validation/validator/identical.c phalcon/validation/validator/inclusionin.c phalcon/validation/validator/presenceof.c phalcon/validation/validator/regex.c phalcon/validation/validator/stringlength.c phalcon/validation/validator/url.c phalcon/validation/validatorinterface.c phalcon/version.c phalcon/annotations/scanner.c phalcon/annotations/parser.c phalcon/mvc/model/query/scanner.c phalcon/mvc/model/query/parser.c phalcon/mvc/view/engine/volt/parser.c phalcon/mvc/view/engine/volt/scanner.c"
	PHP_NEW_EXTENSION(phalcon, $phalcon_sources, $ext_shared)

	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS $INCLUDES"

	AC_CHECK_DECL(
		[HAVE_BUNDLED_PCRE],
		[
			AC_CHECK_HEADERS(
				[ext/pcre/php_pcre.h],
				[
					PHP_ADD_EXTENSION_DEP([phalcon], [pcre])
					AC_DEFINE([ZEPHIR_USE_PHP_PCRE], [1], [Whether PHP pcre extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	AC_CHECK_DECL(
		[HAVE_JSON],
		[
			AC_CHECK_HEADERS(
				[ext/json/php_json.h],
				[
					PHP_ADD_EXTENSION_DEP([phalcon], [json])
					AC_DEFINE([ZEPHIR_USE_PHP_JSON], [1], [Whether PHP json extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	CPPFLAGS=$old_CPPFLAGS
fi
