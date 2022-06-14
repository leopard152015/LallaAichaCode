library(ggplot2)
library(dplyr)
library(plotly)
library(hrbrthemes)
library(data.table)
library(tidyr)

time <- data.table(Time=c(2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021),
real_data = c(10, 18, 13, 18, 14, 10, 8, 6, 6),
kf_gp = c(11.558097, 18.223413, 13.899491, 16.144405, 14.307184, 11.312860, 7.222599, 6.066012, 6.712155),
gp = c(11.558097, 18.223413, 13.899491, 16.144405, 14.307184, 13.009025, 6.359859, 6.066012, 8.592157)
)


predict <- gather(data=time, key = TYPE, value = VAL, real_data, kf_gp, gp)

p <- predict %>%
    ggplot(   aes(x=Time, y=VAL, color=TYPE)) +
    geom_line() + geom_point()+
    theme_ipsum() + 
    scale_x_continuous(name="Years", breaks=seq(2013,2021,1))+
    scale_y_continuous(name="Taux d'admis au BAC M",
    limits= ~c(1,30))

ggsave("taux-admis-bac-M.png")

# Turn it interactive with ggplotly
p <- ggplotly(p)
