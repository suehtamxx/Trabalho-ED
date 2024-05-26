project(
  'work_01-TAD-Lista',
  'c',
  version: '0.1',
  default_options: ['warning_level=3'],
)

subdir('src/image')

includes = [includes_img_trat]
libs = lib_img

configure_file(
  input: 'utils/input_image_example_Gray.txt',
  output: 'imgGray.txt',
  copy: true,
)

configure_file(
  input: 'utils/input_image_example_RGB.txt',
  output: 'imgRGB.txt',
  copy: true,
)


executable(
  'work_01-TAD-Lista',
  'main.c',
  include_directories: includes,
  link_with: libs,
  install: true,
)