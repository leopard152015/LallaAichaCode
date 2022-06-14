library(ggplot2)
library(dplyr)
library(plotly)
library(hrbrthemes)
library(data.table)
library(tidyr)

time <- data.table(Time = c(2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021),
real_data = c(55, 55, 54, 53, 59, 58, 46, 62, 60),
gp_kf = c(54.569107, 53.857059, 54.654968, 55.843254, 59.542759, 57.801712, 46.246807, 56.943539, 56.501095),
gp = c(54.569107, 53.857059, 54.654968, 55.843254, 51.892948, 57.801712, 46.246807, 51.254784, 50.157913)

)


predict <- gather(data=time, key = TYPE, value = VAL, real_data, gp_kf, gp)

p <- predict %>%
     ggplot(   aes(x=Time, y=VAL, color=TYPE)) +
     geom_line() + geom_point()+
     theme_ipsum() + 
     scale_x_continuous(name="Years", breaks=seq(2013,2021,1))+
     scale_y_continuous(name="Taux d'admis à la 1ere session", 
     limits= ~c(10,90))

ggsave("taux-admis-1-session.png")

# Turn it interactive with ggplotly
p <- ggplotly(p)
