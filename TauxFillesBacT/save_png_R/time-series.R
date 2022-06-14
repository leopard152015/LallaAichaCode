library(ggplot2)
library(dplyr)
library(plotly)
library(hrbrthemes)
library(data.table)
library(tidyr)

time <- data.table( Time = c(2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021),
real_data = c(7, 9, 9, 14, 14, 12, 16, 18, 22),
kf_gp = c(6.199597, 10.192638, 8.717151, 12.764447, 13.164519, 11.613432, 14.825608, 16.107777, 17.549301),
gp = c(6.199597, 10.192638, 8.717151, 12.764447, 7.734899, 11.613432, 14.825608, 9.754926, 13.093375)
)


predict <- gather(data=time, key = TYPE, value = VAL, real_data, kf_gp, gp)

p <- predict %>%
    ggplot(   aes(x=Time, y=VAL, color=TYPE)) +
    geom_line() + geom_point()+
    theme_ipsum() + 
    scale_x_continuous(name="Years", breaks=seq(2013,2021,1))+
    scale_y_continuous(name="Taux de filles avec un bac technique",
    limits= ~c(1,25))

ggsave("taux-filles-bac-T.png")

# Turn it interactive with ggplotly
p <- ggplotly(p)
