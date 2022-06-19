library(ggplot2)
library(dplyr)
library(plotly)
library(hrbrthemes)
library(data.table)
library(tidyr)


f <- file("../result.txt")
time <- read.table(f, header= TRUE );
predict <- gather(data=time, key = TYPE, value = VAL, real_data, gp_kf, gp)

p <- predict %>%
     ggplot(   aes(x=Time, y=VAL, color=TYPE)) +
     geom_line() + geom_point()+
     theme_ipsum() + 
     scale_x_continuous(name="Years", breaks=seq(2013,2024,1))+
     scale_y_continuous(name="Taux d'admis à la 1ere session", 
     limits= ~c(10,90))

ggsave("taux-admis-1-session.png")

# Turn it interactive with ggplotly
p <- ggplotly(p)
