data <- read.csv('../output/ecg_out.txt', header=T)

raw <- as.numeric(data$raw) 
mwi <- as.numeric(data$mwi)

ylim <- c(min(data), max(data))

# draw pulse
plot(raw, type="l", ylim = ylim, col = "blue", xlim = c(0000, 10000), axes = T, ann = F)

lines(mwi, col = "red")

title("Pulse", xlab = "Time (s)", ylab = "Pulse (mwi)")

# add zero-line
abline(h=0)
