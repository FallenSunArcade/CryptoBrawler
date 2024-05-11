export default class Splash extends Phaser.Scene {
    constructor() {
        super({key: "splash"});
    }

    create() {
        this.width = this.sys.game.config.width;
        this.height = this.sys.game.config.height;
        this.center_width = this.width / 2;
        this.center_height = this.height / 2;

        const buttonWidth = 150;
        const buttonHeight = 50;
        const buttonX = this.center_width - buttonWidth / 2;
        const buttonY = this.center_height - buttonHeight / 2;

        let button = this.add.graphics();
        button.fillStyle(0x0000ff, 1);
        button.fillRect(buttonX, buttonY, buttonWidth, buttonHeight);

        let buttonText = this.add.text(0, 0, 'Start', {
            font: '20px Arial',
            fill: '#ffffff'
        });

        buttonText.setOrigin(0.5, 0.5);
        buttonText.setPosition(buttonX + buttonWidth / 2, buttonY + buttonHeight / 2);

        button.setInteractive(new Phaser.Geom.Rectangle(buttonX, buttonY, buttonWidth, buttonHeight), Phaser.Geom.Rectangle.Contains);

        button.on('pointerdown', () => {
            console.log('Button pressed!');
        });

        button.on('pointerover', () => {
            button.clear();
            button.fillStyle(0x000077, 1);
            button.fillRect(buttonX, buttonY, buttonWidth, buttonHeight);
        });

        button.on('pointerout', () => {
            button.clear(); 
            button.fillStyle(0x0000ff, 1);
            button.fillRect(buttonX, buttonY, buttonWidth, buttonHeight);
        });
    }
}