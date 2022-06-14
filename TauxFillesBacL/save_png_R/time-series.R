library(ggplot2)
library(dplyr)
library(plotly)
library(hrbrthemes)
library(data.table)
library(tidyr)

time <- data.table( Time = c(2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021),
real_data = c(37, 34, 36, 34, 37, 43, 36, 39, 38),
kf_gp = c(36.999283, 33.998886, 36.000301, 33.997227, 37.455544, 43.003208, 36.002285, 41.110317, 39.245167),
gp = c(36.999283, 33.998886, 36.000301, 33.997227, 37.455544, 43.003208, 36.002285, 35.274437, 34.470280)
)

predict <- gather(data=time, key = TYPE, value = VAL, real_data, kf_gp, gp)

# Usual area chart
p <- predict %>%
    ggplot(   aes(x=Time, y=VAL, color=TYPE)) +
    geom_line() + geom_point()+
    theme_ipsum() + 
    scale_x_continuous(name="Years", breaks=seq(2013,2021,1))+
    scale_y_continuous(name="Taux de filles avec un bac litérraires",
    limits= ~c(25,50))

ggsave("taux-filles-bac-L.png")

# Turn it interactive with ggplotly
p <- ggplotly(p)
