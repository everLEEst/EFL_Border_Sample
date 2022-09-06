project('EFL Border Sample',                                                                                                                                                                                                'c',
        license : 'Apache')

sample_deps = [
    dependency('elementary'),
    dependency('appcore-efl'), 
    dependency('dlog'), 
]

sample_inc = [
   include_directories('inc'), 
]

subdir('res')

executable('EFL-Border-Sample', 'src/main.c',
           dependencies: sample_deps,
           include_directories: sample_inc,
           install : true,
		   install_dir:  join_paths(get_option('tzapp_path'), 'EFL-Border-Sample', 'bin'),
		   )

install_data('EFL-Border-Sample.xml', install_dir: get_option('tzpackage_path'))
