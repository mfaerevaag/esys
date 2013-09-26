data <- read.csv('../output/ecg_out.txt', header=T)

raw <- as.numeric(data$raw) 
mwi <- as.numeric(data$mwi)

ylim <- c(min(data), max(data))

title("Pulse", xlab = "Time (s)", ylab = "Pulse (mwi)")
# draw pulse
plot(raw, type="l", ylim = ylim, col = "blue", xlim = c(0000, 5000))#, axes = F, ann = F)
lines(mwi, col = "red")

# add zero-line
abline(h=0)
