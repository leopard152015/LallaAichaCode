library(ggplot2)
library(dplyr)
library(plotly)
library(hrbrthemes)
library(data.table)
library(tidyr)

time <- data.table( Time = c(2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021),
real_data = c(31, 30, 33, 33, 39, 40, 39, 44, 42),
kf_gp = c(31.017639, 30.754190, 32.836090, 32.768028, 38.276306, 40.927322, 38.556179, 42.490627, 42.143188),
gp = c(31.017639, 30.754190, 32.836090, 32.768028, 32.226158, 40.927322, 38.556179, 34.099258, 35.250359)
)

predict <- gather(data=time, key = TYPE, value = VAL, real_data, kf_gp, gp)

# Usual area chart
p <- predict %>%
    ggplot(   aes(x=Time, y=VAL, color=TYPE)) +
    geom_line() + geom_point()+
    theme_ipsum() + 
    scale_x_continuous(name="Years", breaks=seq(2013,2021,1))+
    scale_y_continuous(name="Taux de filles avec un bac scientifique",
    limits= ~c(25,50))

ggsave("taux-filles-bas-S.png")

# Turn it interactive with ggplotly
p <- ggplotly(p)
