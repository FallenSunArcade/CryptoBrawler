import Phaser from 'phaser';
import PhaserMatterCollisionPlugin from "phaser-matter-collision-plugin";
import Bootloader from "./scenes/bootloader.js";
import Splash from "./scenes/splash.js";

const config= {
    width: 960,
    height: 540,
    type: Phaser.AUTO,
    scale: {
        mode: Phaser.Scale.FIT,
        autoCenter: Phaser.Scale.CENTER_BOTH,
    },
    autoRound: false,
    parent: "crypto-brawler",
    physics: {
        default: "matter",
        matter: {
            debug: false,
        },
    },
    plugins: {
        scene: [
            {
                plugin: PhaserMatterCollisionPlugin, 
                key: "matterCollision",
                mapping: "matterCollision",
            }
        ],
    },
    scene: [Bootloader, Splash],
};

const game = new Phaser.Game(config);

