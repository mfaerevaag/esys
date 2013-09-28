data <- read.csv('../output/data.csv', header=T)

time <- as.numeric(data$time)
raw <- as.numeric(data$raw) 
mwi <- as.numeric(data$mwi)


pdf("graphs/r_peaks.pdf")

# draw pulse
plot(mwi, type="l", col = "red", xlim = c(0, 5000), axes = T, ann = F)

# plot the r peak points
xp <- c(154 ,322 ,479 ,627 ,785 ,953 ,1102,1261,1419,1577,1734,1901,2048,2174,2352,2503,2659,2822,2979,3137,3306,3455,3614,3772,3928,4087,4244,4401,4559,4687,4862)

yp <- c(4626,4263,4519,4933,4436,4370,4102,4485,4544,4341,4392,4431,4380,4121,3928,3834,4640,4061,4093,4218,4669,4433,4553,4981,4892,3996,4562,3920,3612,3856,3979)

points(xp, yp)

title("R-Peaks", xlab = "Time (samples)", ylab = "MWI")
    
# add zero-line
abline(h=0)

dev.off()
