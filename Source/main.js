import '../style.css'
import Phaser from 'phaser'

const canvasSize={
    width:600,
    height:500
}

const config = {
    type:Phaser.AUTO,
    width:canvasSize.width,
    height:canvasSize.height
}

const game = new Phaser.Game(config)
