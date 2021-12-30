function(add_auto_break_test TARGET FILES)
  message(STATUS "[auto-break] Adding test `${TARGET}` with files `${FILES}`")
  add_executable("${TARGET}" ${FILES})
endfunction()
