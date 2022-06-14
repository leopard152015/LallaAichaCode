#!/bin/bash

echo "Launching plot script..."
R < time-series.R --save > plot_info

echo "Done"
