# bokeh_emu

Add realistic pseudo bokeh effect to given photo image.

## Description

bokeh_emu is command line tool that generates image with pseudo bokeh effect.

## Examples

Original image (Size: 1920 x 1230)

<img src="https://raw.githubusercontent.com/wiki/delphinus1024/bokeh_emu/image/before.png" style="width: 600px;"/>

Kernel and processed image with parameter (-k ./kernel/poly9_kernel.tif -r 45 -b 8 -g 3.0)

![Kernel](https://github.com/delphinus1024/bokeh_emu/blob/master/kernel/poly9_kernel.tif)

<img src="https://raw.githubusercontent.com/wiki/delphinus1024/bokeh_emu/image/poly9-r45-b8-g3_0.png" style="width: 600px;"/>

Kernel and processed image with parameter (-k ./kernel/poly9_kernel.tif -r 111 -b 8 -g 3.0)

![Kernel](https://github.com/delphinus1024/bokeh_emu/blob/master/kernel/poly9_kernel.tif)

<img src="https://raw.githubusercontent.com/wiki/delphinus1024/bokeh_emu/image/poly9-r111-b8-g3_0.png" style="width: 600px;"/>

Kernel and processed image with parameter (-k ./kernel/circle2_kernel.tif -r 131 -g 3.0)

![Kernel](https://github.com/delphinus1024/bokeh_emu/blob/master/kernel/circle2_kernel.tif)

<img src="https://raw.githubusercontent.com/wiki/delphinus1024/bokeh_emu/image/circle2-r131-g3_0.png" style="width: 600px;"/>

Kernel and processed image with parameter (-k ./kernel/donut_kernel.tif -r 111 -b 8 -g 1.9)

![Kernel](https://github.com/delphinus1024/bokeh_emu/blob/master/kernel/donut_kernel.tif)

<img src="https://raw.githubusercontent.com/wiki/delphinus1024/bokeh_emu/image/donut-r111-b8-g1_9.png" style="width: 600px;"/>

Kernel and processed image with parameter (-k ./kernel/star_kernel.tif -r 151 -b 3 -g 1.9)

![Kernel](https://github.com/delphinus1024/bokeh_emu/blob/master/kernel/star_kernel.tif)

<img src="https://raw.githubusercontent.com/wiki/delphinus1024/bokeh_emu/image/star-r151-b3-g1_9.png" style="width: 600px;"/>

## Features

- Generates image with realistic bokeh effect.
- User can specify arbitrary kernel shape so that it can control the shape of the bokeh effect. User can also resize the kernel image before processing so that it can control the size (diameter) of the bokeh effect.
- Some values can be parameterized to control the degree of strength of the bokeh effect.

## Requirement

- OpenCV 3.0.0 or above is preferable.
- Checked with win7 32bit + msys2 + gcc

## Usage

1. Type following command in your command window.
$ bokeh_emu -i input_image -k kernel_image [-o output image] [-r kernel resize value] [-b gaussian sigma for kernel] [-g gamma] [-s]
3. [] is optional.

- -i input image file:    Original image file.
- -k kernel image file:   Kernel image file to detemine the shape of bokeh. It must be gray scaled (one channel) image. I added some kernel examples image files under 'kernel' folder. 
- -o output image file:   Output image file. (default: result.tif)
- -r kernel resize:  Resize the kernel image before processing. The larger the kernel size, the larger the bokeh shape. (default: no resize)
- -b gaussian sigma for kernel:   Blur the kernel image before processing, to make the final bokeh softer. (default: no blur)
- -g gamma:          Gamma correction factor. correction is done before processing and reverse gamma corrention is done after processing.  Larger gamma value gives larger bokeh effect to bright area. (default: 2.2)
- -s:              Add this option when show the original and processed image when finished.
	
## Installation

1. Modify Makefile according to your OpenCV inludes and libs environment.
2. make

## Author

delphinus1024

## License

[MIT](https://raw.githubusercontent.com/delphinus1024/diff_filter_emu/master/LICENSE.txt)

