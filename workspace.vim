
"开启tags补全引擎， 只支持ctags， 必须使用 --fields=——l选项
"let g:ycm_collect_identifiers_from_tags_files = 0


command! Todo Ack! 'TODO|FIXME|CHANGED|BUG|HACK'

let PROJECT_HOME = $PWD


func! Debug()
     exec "packadd termdebug"
     exec "let g:termdebug_wide = 163"
     exec "Termdebug"
 endfunc



