# roi-marker
A simple marker of (rectangular) Region of Interest (ROI) in images.

## Description

This application was developed mainly for developers of 
computer vision applications who aims to detect rectangular
regions on images. The need for it came from my current 
research project on License Plate Recognition systems, since
I need a way of saying where the plates are located in
an image (and, also, what is the content of them), and, then,
measure the accuracy of the system.

The current version admits only rectangular regions and
content indication, with a still very poor, but functional, layout design,
one of the factors to be improved in next steps.

It has been developed in pure C++ and wxWidgets GUI library. One of the
most important features is the storage of the information of interest
using XMP image metadata, through the Exiv2 library. This one allows the
application to write metadata about the rectangles and its content and, after,
retrieve them in order to check, for example, the accuracy of
some detector.

## Installation

You will need, besides the classic packages regarding to C++ compilation,
the exiv2, wxWidgets and boost libraries.

## Doubts?

Refer to my e-mail, greati@ufrn.edu.br.

