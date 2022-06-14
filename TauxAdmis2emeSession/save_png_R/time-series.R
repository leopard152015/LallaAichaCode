library(ggplot2)
library(dplyr)
library(plotly)
library(hrbrthemes)
library(data.table)
library(tidyr)


time <- data.table(Time = c(2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021),
real_data = c(45, 45, 46, 47, 41, 42, 54, 38, 40),
kf_gp = c(44.923817, 45.000549, 46.026833, 46.995529, 41.104073, 42.009346, 54.059299, 41.216621, 37.712574),
gp = c(44.923817, 45.000549, 46.026833, 46.995529, 46.408981, 42.009346, 54.059299, 44.607395, 40.59639))


predict <- gather(data=time, key = TYPE, value = VAL, real_data, kf_gp, gp)

p <- predict %>%
     ggplot(   aes(x=Time, y=VAL, color=TYPE)) +
     geom_line() + geom_point()+
     theme_ipsum() + 
     scale_x_continuous(name="Years", breaks=seq(2013,2021,1))+
     scale_y_continuous(name="Taux d'admis à la 2eme session",
     limits= ~c(10,90))

ggsave("taux-adims-2-session.png")

# Turn it interactive with ggplotly
p <- ggplotly(p)
