import * as THREE from 'three';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setAnimationLoop(animate);
document.body.appendChild(renderer.domElement);

camera.position.z = 2;

function createMengerSponge(size, depth) {
    const group = new THREE.Group();
    
    if (depth === 0) {
        const geometry = new THREE.BoxGeometry(size, size, size);
        const material = new THREE.MeshBasicMaterial({ color: 0x00ff00, wireframe: true });
        const cube = new THREE.Mesh(geometry, material);
        group.add(cube);
    } else {
        const newSize = size / 3;
        for (let x = -1; x <= 1; x++) {
            for (let y = -1; y <= 1; y++) {
                for (let z = -1; z <= 1; z++) {
                    const sum = Math.abs(x) + Math.abs(y) + Math.abs(z);
                    if (sum > 1) {
                        const subGroup = createMengerSponge(newSize, depth - 1);
                        subGroup.position.set(x * newSize, y * newSize, z * newSize);
                        group.add(subGroup);
                    }
                }
            }
        }
    }

    return group;
}

const fractal = createMengerSponge(2, 3);
scene.add(fractal);

function animate() {
    //fractal.rotation.x += 0.01;
    fractal.rotation.y += 0.01;
    renderer.render(scene, camera);
}
