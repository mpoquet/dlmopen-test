project('dlmopen-test-user', 'c', default_options : ['c_std=c11'])

base_dep = dependency('base')

shared_library('user', 'user.c',
  install: true,
  dependencies: [base_dep],
  c_args: '-DVERSION=@0@'.format(get_option('version'))
)
