import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;

public class yu {

    public static void main(String[] args) {
        try {
            String inputPath = "C:\\Users\\user\\Desktop\\1113405010\\images.png";
            String xOutputPath = "x_output.jpg";
            String yOutputPath = "y_output.jpg";

            File inputFile = new File(inputPath);

            if (!inputFile.exists()) {
                System.out.println("找不到 input.jpg，請把圖片放在程式同一個資料夾");
                return;
            }

            BufferedImage img = ImageIO.read(inputFile);

            int w = img.getWidth();
            int h = img.getHeight();

            int[][] gray = new int[w][h];

            // 先把原圖轉成灰階數值
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    Color c = new Color(img.getRGB(x, y));
                    int g = (c.getRed() + c.getGreen() + c.getBlue()) / 3;
                    gray[x][y] = g;
                }
            }

            BufferedImage xImage = new BufferedImage(w, h, BufferedImage.TYPE_BYTE_GRAY);
            BufferedImage yImage = new BufferedImage(w, h, BufferedImage.TYPE_BYTE_GRAY);

            // 掃描 X 方向：左右亮度差
            for (int y = 0; y < h; y++) {
                for (int x = 1; x < w - 1; x++) {
                    int ix = Math.abs(gray[x + 1][y] - gray[x - 1][y]);

                    if (ix > 255) {
                        ix = 255;
                    }

                    Color color = new Color(ix, ix, ix);
                    xImage.setRGB(x, y, color.getRGB());
                }
            }

            // 掃描 Y 方向：上下亮度差
            for (int y = 1; y < h - 1; y++) {
                for (int x = 0; x < w; x++) {
                    int iy = Math.abs(gray[x][y + 1] - gray[x][y - 1]);

                    if (iy > 255) {
                        iy = 255;
                    }

                    Color color = new Color(iy, iy, iy);
                    yImage.setRGB(x, y, color.getRGB());
                }
            }

            ImageIO.write(xImage, "jpg", new File(xOutputPath));
            ImageIO.write(yImage, "jpg", new File(yOutputPath));

            System.out.println("完成！");
            System.out.println("原圖：" + inputPath);
            System.out.println("X方向掃描結果：" + xOutputPath);
            System.out.println("Y方向掃描結果：" + yOutputPath);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}