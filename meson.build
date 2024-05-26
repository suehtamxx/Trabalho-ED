project(
  'work_01-TAD-Lista',
  'c',
  version: '0.1',
  default_options: ['warning_level=3'],
)

subdir('src/image')

includes = [includes_img_trat]
libs = lib_img


executable(
  'work_01-TAD-Lista',
  'main.c',
  include_directories: includes,
  link_with: libs,
  install: true,
)