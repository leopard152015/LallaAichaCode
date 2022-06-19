library(ggplot2)
library(dplyr)
library(plotly)
library(hrbrthemes)
library(data.table)
library(tidyr)

f <- file("../result.txt")
time <- read.table(f, header= TRUE );


predict <- gather(data=time, key = TYPE, value = VAL, real_data, kf_gp, gp)

# Usual area chart
p <- predict %>%
    ggplot(   aes(x=Time, y=VAL, color=TYPE)) +
    geom_line() + geom_point()+
    theme_ipsum() + 
    scale_x_continuous(name="Years", breaks=seq(2013,2024,1))+
    scale_y_continuous(name="Taux de filles avec un bac litérraires",
    limits= ~c(25,50))

ggsave("taux-filles-bac-L.png")

# Turn it interactive with ggplotly
p <- ggplotly(p)
