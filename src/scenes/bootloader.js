export default class Bootloader extends Phaser.Scene {
    constructor() {
        super({key: "bootloader"});
    }

    preload() {
        this.createBars();
        this.setLoadEvents();
    }
    setLoadEvents() {
        this.load.on(
            "progress",
            function (value) {
                this.progressBar.clear();
                this.progressBar.fillStyle(0x0088aa, 1);
                this.progressBar.fillRect(
                    this.cameras.main.width / 4,
                    this.cameras.main.height / 2 - 16,
                    (this.cameras.main.width / 2) * value,
                    16
                );
            },
            this
        );

        this.load.on(
            "complete",
            () => {
                this.scene.start("splash");
            },
            this
        );
    }

    createBars() {
        this.loadBar = this.add.graphics();
        this.loadBar.fillStyle(0x00aafb, 1);
        this.loadBar.fillRect(
            this.cameras.main.width / 4 - 2,
            this.cameras.main.height / 2 - 18,
            this.cameras.main.width / 2 + 4,
            20
        );
        this.progressBar = this.add.graphics();
    }
}