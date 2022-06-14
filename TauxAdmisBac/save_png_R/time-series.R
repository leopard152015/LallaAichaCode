library(ggplot2)
library(dplyr)
library(plotly)
library(hrbrthemes)
library(data.table)
library(tidyr)

time <- data.table( Time = c(2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021), 
real_data = c(5696, 5017, 5782, 5081, 6693, 11114, 7094, 11658, 6234),
gp_kf = c(5695.764648, 5017.083008, 5782.005371, 5080.961426, 6696.941406, 11114.190430, 7849.318848, 8197.150391, 8097.964844),
gp = c(5695.764648, 5017.083008, 5782.005371, 5080.961426, 4701.252930, 11114.190430, 7849.318848, 4319.094727, 5926.021484)
)


predict <- gather(data=time, key = TYPE, value = VAL, real_data, gp_kf, gp)

p <- predict %>%
     ggplot(   aes(x=Time, y=VAL, color=TYPE)) +
     geom_line() + geom_point()+
     theme_ipsum() + 
     scale_x_continuous(name="Years", breaks=seq(2013,2021,1))+
     scale_y_continuous(name="Taux d'admis au BAC (tout bac inclut)", 
     limits= ~c(900,20000))

ggsave("taux-admis-bac.png")

# Turn it interactive with ggplotly
p <- ggplotly(p)
